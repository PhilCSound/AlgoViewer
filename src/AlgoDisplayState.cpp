#include "AlgoDisplayState.hpp"

void AlgoDisplayState::OnEntry(Application* app)
{
    m_tgui.setTarget(app->GetWindow());
    createUI();
    m_randomGenerator.seed(std::random_device{}());
    m_shortData.reserve(m_numDataEntries);
    m_shortData.resize(m_numDataEntries);
    generateLinearData();
    
}

void AlgoDisplayState::OnExit(Application* app)
{
}

void AlgoDisplayState::Draw(sf::RenderWindow & window)
{
    window.setView(m_displayView);
    m_dataDisplay.draw(window, sf::RenderStates());
    m_tgui.draw();
}

void AlgoDisplayState::Update(Application* app, sf::Time elapTime)
{
    if (m_begin)
    {
        tgui::ProgressBar::Ptr progressBar = m_tgui.get<tgui::ProgressBar>("Progress");

        if (!m_dataDisplay.isAnimating())
        {
            if(m_commands.empty())
            {
                m_dataDisplay.resetIndexes();
                doneWithAlgorithm();
                return;
            }
            Command* cmd = m_commands.front();
            cmd->execute(m_dataDisplay);
            std::string stringToLog = cmd->toString();
            if (!stringToLog.empty())
                log(cmd->toString());
            m_commands.pop_front();
            m_usedCommands.push_back(cmd);
            if (progressBar)
                progressBar->setValue(m_usedCommands.size());
        }
        else
            m_dataDisplay.update(elapTime);
    }
}

void AlgoDisplayState::HandleEvent(sf::Event& event, sf::RenderWindow & window)
{
    m_tgui.handleEvent(event);
    if(!m_begin)
    {
        switch (event.type)
        {
            //Event here
            default:
                break;
        }
    }
}

void AlgoDisplayState::Pause()
{
}

void AlgoDisplayState::Unpause()
{
}

void AlgoDisplayState::shuffleData()
{
    m_usedCommands.clear(); //Fixes a bug where replay messes up
    std::shuffle(m_shortData.begin(), m_shortData.end(), m_randomGenerator);
    updateDisplayView();
}

void AlgoDisplayState::generateLinearData()
{
    m_usedCommands.clear(); //Fixes a bug where replay messes up
    for (auto i = 0; i < m_shortData.size(); i++)
        m_shortData[i] = i + 1;
    updateDisplayView();
}

void AlgoDisplayState::generateRandomData()
{
    m_usedCommands.clear(); //Fixes a bug where replay messes up
    std::uniform_int_distribution dist { 1, m_numDataEntries + 1 };
    for (auto i = 0; i < m_shortData.size(); i++)
        m_shortData[i] = dist(m_randomGenerator);
    updateDisplayView();
}

void AlgoDisplayState::resizeData()
{
    tgui::Slider::Ptr slider = m_tgui.get<tgui::Slider>("SizeSlider");
    if (!slider)
        return;
    else if (slider->getValue() < 3)
        return;
    
    unsigned int size = static_cast<unsigned int>(slider->getValue());
    unsigned int oldSize = m_shortData.size();

    tgui::Label::Ptr lbl = m_tgui.get<tgui::Label>("Num");
    if (lbl)
        lbl->setText(std::to_string(size));

    m_shortData.reserve(size);
    m_shortData.resize(size);
    if (size > oldSize)
        std::fill(m_shortData.begin() + oldSize, m_shortData.end(), 1);

    m_numDataEntries = size;
    updateDisplayView();
    //Gets rid of a nasty out of bounds error when you replay:
    m_commands.clear();
    m_usedCommands.clear();
}


/*
|   This functions gonna be a mess....
*/
void AlgoDisplayState::createUI()
{
    m_tgui.loadWidgetsFromFile("resources/ui/ui.txt");
    tgui::Button::Ptr shuffleButton = m_tgui.get<tgui::Button>("Shuffle");
    if (shuffleButton)
        shuffleButton->onPress(&AlgoDisplayState::shuffleData, this);

    tgui::Button::Ptr lineData = m_tgui.get<tgui::Button>("GenLinearData");
    if (lineData)
        lineData->onPress(&AlgoDisplayState::generateLinearData, this);

    tgui::Button::Ptr ranData = m_tgui.get<tgui::Button>("GenRandomData");
    if (ranData)
        ranData->onPress(&AlgoDisplayState::generateRandomData, this);

    tgui::Button::Ptr beginButton = m_tgui.get<tgui::Button>("Begin");
    if (beginButton)
        beginButton->onPress(&AlgoDisplayState::beginAlgorithm, this, false);

    tgui::Button::Ptr replayButton = m_tgui.get<tgui::Button>("Replay");
    if (replayButton)
        replayButton->onPress(&AlgoDisplayState::beginAlgorithm, this, true);

    tgui::Slider::Ptr slider = m_tgui.get<tgui::Slider>("SizeSlider");
    if (slider)
        slider->onValueChange(&AlgoDisplayState::resizeData, this);


    tgui::ComboBox::Ptr sortBox = m_tgui.get<tgui::ComboBox>("Sort");
    if (sortBox)
    {

        sortBox->addItem("Selection Sort");
        sortBox->setSelectedItemByIndex(0);
        m_algoName = sortBox->getSelectedItem().toStdString();
        m_selectedAlgo = SortAlgoEnum::SelectionSort;
        sortBox->addItem("Insertion Sort");
        sortBox->addItem("Merge Sort");
        sortBox->addItem("Radix Sort");
        
    }
}

void AlgoDisplayState::updateDisplayView()
{
    m_dataDisplay.setData(m_shortData);
    m_displayView = m_dataDisplay.getView();
    m_displayView.setViewport(sf::FloatRect( 0.0f, 0.2f, 1.0f, 0.8f));
}

void AlgoDisplayState::beginAlgorithm(bool replay)
{
    m_begin = true;
    if (replay)
    {
        m_commands = m_usedCommands;
        updateDisplayView();
    }
    else
    {
        tgui::ComboBox::Ptr sortBox = m_tgui.get<tgui::ComboBox>("Sort");
        if (!sortBox)
            return;
        m_algoName = sortBox->getSelectedItem().toStdString();
        m_selectedAlgo = (SortAlgoEnum) sortBox->getSelectedItemIndex();
        sf::Clock clock;
        setAlgorithm(false);
        log(m_algoName + " completed in: " + 
            std::to_string((int)clock.getElapsedTime().asMicroseconds()) + " microseconds.");
        setAlgorithm(true);
    }

    m_usedCommands.clear();
    
    auto panel = m_tgui.get<tgui::Panel>("BeginPanel");
    if (panel)
        panel->setVisible(false);

    auto progressBar = m_tgui.get<tgui::ProgressBar>("Progress");
    if (progressBar)
    {
        progressBar->setValue(0);
        progressBar->setMaximum(m_commands.size());
    }
}

void AlgoDisplayState::setAlgorithm(bool time)
{
    switch (m_selectedAlgo)
    {
        default:
            m_commands = Algo::SelectionSort(m_shortData, time);
            break;
        case SortAlgoEnum::SelectionSort:
            m_commands = Algo::SelectionSort(m_shortData, time);
            break;
        case SortAlgoEnum::InsertionSort:
            m_commands = Algo::InsertionSort(m_shortData, time);
            break;
        case SortAlgoEnum::MergeSort:
            break;
        case SortAlgoEnum::RadixSort:
            break;
    }
}


void AlgoDisplayState::doneWithAlgorithm()
{
    m_begin = false;
    
    auto panel = m_tgui.get<tgui::Panel>("BeginPanel");
    if (panel)
        panel->setVisible(true);
    
    auto progressBar = m_tgui.get<tgui::ProgressBar>("Progress");
    if (progressBar)
        progressBar->setValue(0);

    auto logger = m_tgui.get<tgui::ChatBox>("Log");
    if (logger)
        logger->removeAllLines();
}

void AlgoDisplayState::log(const std::string string)
{
    auto logger = m_tgui.get<tgui::ChatBox>("Log");
    if (logger)
        logger->addLine(string);
}
