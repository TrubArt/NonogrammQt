#include "conditionlevelcreate.h"
#include "ui_conditionlevelcreate.h"
#include "../utils.h"
#include "../levelsManager/levelLoader/fileParser.h"
#include "../levelsManager/levelLoader/checker.h"

ConditionLevelCreate::ConditionLevelCreate(const QStringList& levelsName, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::ConditionLevelCreate)
    , m_levelsName(levelsName)
{
    ui->setupUi(this);
    setWindowTitle(tr("Level Creation"));
    ui->buttonNext->setFocus();
    ui->stackedWidget->setCurrentIndex(0);

    m_sections.reserve(ui->sectionsLayout->rowCount());
    for (int i = 0; i < ui->sectionsLayout->rowCount(); ++i)
    {
        m_sections.push_back(static_cast<QLabel*>(ui->sectionsLayout->itemAtPosition(i, 0)->widget()));
    }

    m_linesContents = scrollAreaInit(ui->LineScrollArea);
    m_columnsContents = scrollAreaInit(ui->ColumnScrollArea);
    m_additionContents = scrollAreaInit(ui->AdditionScrollArea);

    connectInitialization();
}

ConditionLevelCreate::~ConditionLevelCreate()
{
    delete ui;
}

ScrollAreaConditionContent* ConditionLevelCreate::scrollAreaInit(QScrollArea* scrollArea)
{
    ScrollAreaConditionContent* content = new ScrollAreaConditionContent();
    scrollArea->setWidget(content);
    content->setScrollArea(scrollArea);

    return content;
}

void ConditionLevelCreate::connectInitialization()
{
    connect(ui->buttonCancel, &QPushButton::clicked, this, &ConditionLevelCreate::reject);
    connect(ui->buttonBack, &QPushButton::clicked, this, &ConditionLevelCreate::backClicked);
    connect(ui->buttonNext, &QPushButton::clicked, this, &ConditionLevelCreate::nextClicked);
    connect(ui->pbAdd, &QPushButton::clicked, this, &ConditionLevelCreate::addClicked);
    connect(ui->pbDelete, &QPushButton::clicked, this, &ConditionLevelCreate::deleteClicked);
}

void ConditionLevelCreate::backClicked()
{
    int oldIndex = ui->stackedWidget->currentIndex();
    if (!checkDataValidation(oldIndex))
    {
        return;
    }

    int newIndex = oldIndex - 1;

    if (oldIndex == ui->stackedWidget->count() - 1)
    {
        ui->buttonNext->setText("Next");
    }

    if (newIndex == 0)
    {
        ui->buttonBack->setEnabled(false);
    }

    ui->stackedWidget->setCurrentIndex(newIndex);
    setSectionsFont(newIndex, ButtonClicked::back);
}

void ConditionLevelCreate::nextClicked()
{
    int oldIndex = ui->stackedWidget->currentIndex();
    if (!checkDataValidation(oldIndex))
    {
        return;
    }

    int countPage = ui->stackedWidget->count();
    if (oldIndex == countPage - 1)
    {
        QDialog::accept();
        return;
    }

    remakeScrollAreaSource();

    int newIndex = oldIndex + 1;

    if (newIndex == countPage - 1)
    {
        ui->buttonNext->setText("Finish");
    }

    ui->buttonBack->setEnabled(true);
    ui->stackedWidget->setCurrentIndex(newIndex);
    setSectionsFont(newIndex, ButtonClicked::next);
}

void ConditionLevelCreate::addClicked()
{
    int oldSize = m_additionContents->getViewSize();
    if (oldSize == 0)
    {
        ui->pbDelete->setEnabled(true);
    }
    m_additionContents->updateContent(oldSize + 1);
}

void ConditionLevelCreate::deleteClicked()
{
    int oldSize = m_additionContents->getViewSize();
    if (oldSize == 1)
    {
        ui->pbDelete->setEnabled(false);
    }
    m_additionContents->updateContent(oldSize - 1);
}

bool ConditionLevelCreate::checkDataValidation(int pageIndex)
{
    switch (pageIndex)
    {
    case 0:
        return firstPageDataCheck();
    case 1:
    case 2:
        return secAndThirdPageDataCheck();
    case 3:
        return fourthPageDataCheck();
    default:
        return false;
    }
}

void ConditionLevelCreate::setSectionsFont(int newPageIndex, ButtonClicked button)
{
    QFont font = m_sections[0]->font();
    if (button == ButtonClicked::back)
    {
        font.setWeight(QFont::Weight::Normal);
        m_sections[newPageIndex + 1]->setFont(font);
    }
    else // ButtonClicked::next
    {
        font.setWeight(QFont::Weight::Bold);
        m_sections[newPageIndex]->setFont(font);
    }
}

bool ConditionLevelCreate::firstPageDataCheck()
{
    bool good = nameCheck();
    if (!good)
    {
        return false;
    }

    const QString errorSizeMessage = tr("Invalid sizes!");
    if (ui->rows->value() <= 0)
    {
        ui->labelRowCount->setStyleSheet(m_errorBack);
        utils::sendMessage(m_errorWindowName, errorSizeMessage);
        return false;
    }
    ui->labelRowCount->setStyleSheet(m_normalBack);

    if (ui->columns->value() <= 0)
    {
        ui->labelColumCount->setStyleSheet(m_errorBack);
        utils::sendMessage(m_errorWindowName, errorSizeMessage);
        return false;
    }
    ui->labelColumCount->setStyleSheet(m_normalBack);

    return true;
}

bool ConditionLevelCreate::nameCheck()
{
    QString newName = ui->levelName->text();
    if (newName.isEmpty() || m_levelsName.contains(newName))
    {
        ui->labelLevelName->setStyleSheet(m_errorBack);
        if (newName.isEmpty())
        {
            utils::sendMessage(m_errorWindowName, m_nameIsEmptyError);
        }
        else
        {
            utils::sendMessage(m_errorWindowName, m_nameExistError);
        }
        return false;
    }
    ui->labelLevelName->setStyleSheet(m_normalBack);
    return true;
}

bool ConditionLevelCreate::secAndThirdPageDataCheck()
{
    return true;
}

bool ConditionLevelCreate::fourthPageDataCheck()
{
    return true;
}

void ConditionLevelCreate::remakeScrollAreaSource()
{
    int rowsCount = ui->rows->value();
    if (rowsCount != m_linesContents->getViewSize())
    {
        m_linesContents->updateContent(rowsCount);
    }

    int columnCount = ui->columns->value();
    if (columnCount != m_columnsContents->getViewSize())
    {
        m_columnsContents->updateContent(columnCount);
    }
}

QString ConditionLevelCreate::getLevelName() const
{
    return ui->levelName->text();
}

DataInformation ConditionLevelCreate::getData() const
{
    DataInformation data_t;

    const QVector<ConditionElement*>& lines = m_linesContents->getConditions();
    const QVector<ConditionElement*>& columns = m_columnsContents->getConditions();
    const QVector<ConditionElement*>& additions = m_additionContents->getConditions();

    data_t.lineConditions = getConditions(lines, m_linesContents->getViewSize());
    data_t.columnConditions = getConditions(columns, m_columnsContents->getViewSize());
    data_t.additionConditions = getAdditions(additions, m_additionContents->getViewSize());

    return data_t;
}

PropertiesInformation ConditionLevelCreate::getProperties() const
{
    PropertiesInformation properties_t;
    properties_t.rowCount = ui->rows->value();
    properties_t.columnCount = ui->columns->value();
    return properties_t;
}

std::vector<std::vector<size_t>> ConditionLevelCreate::getConditions(const QVector<ConditionElement*>& data, int viewSize) const
{
    std::vector<std::vector<size_t>> conditionsList;
    conditionsList.reserve(viewSize);

    for (int i = 0; i < viewSize; ++i)
    {
        const ConditionElement* cond = data[i];
        std::vector<size_t> condition;

        QStringList values;
        QString line = cond->getData();
        FileParser::getLevelData(line, values);

        condition.reserve(values.size());
        for (const QString& value : values)
        {
            condition.push_back(value.toInt());
        }

        conditionsList.push_back(condition);
    }

    return conditionsList;
}

std::vector<std::array<size_t, 3>> ConditionLevelCreate::getAdditions(const QVector<ConditionElement*>& data, int viewSize) const
{
    std::vector<std::array<size_t, 3>> condition;
    condition.reserve(viewSize);

    for (int i = 0; i < viewSize; ++i)
    {
        const ConditionElement* cond = data[i];

        QStringList values;
        QString line = cond->getData();
        FileParser::getLevelData(line, values);

        std::array<size_t, 3> oneAdditionalCondition;
        for (int i = 0; i < 3; ++i)
        {
            oneAdditionalCondition[i] = values[i].toInt();
        }

        condition.push_back(oneAdditionalCondition);
    }

    return condition;
}
