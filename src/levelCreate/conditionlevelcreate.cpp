#include "conditionlevelcreate.h"
#include "ui_conditionlevelcreate.h"
#include "utils.h"
#include "levelsManager/levelLoader/fileParser.h"
#include "levelsManager/levelLoader/checker.h"

#include <QScrollBar>

const QString ConditionLevelCreate::Styles::errorBack = "{border: 1px solid #FF0e1a;}";
const QString ConditionLevelCreate::Styles::normalBack = "{border: 1px solid black;}";

ConditionLevelCreate::ConditionLevelCreate(const QStringList& levelsName, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::ConditionLevelCreate)
    , m_levelsName(levelsName)
{
    ui->setupUi(this);
    setWindowTitle(tr("Level Creation"));
    ui->buttonNext->setFocus();
    ui->stackedWidget->setCurrentIndex(0);

    ui->levelName->setStyleSheet(Styles::lineEditNorm());
    ui->rows->setStyleSheet(Styles::spinBoxNorm());
    ui->columns->setStyleSheet(Styles::spinBoxNorm());

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
    ScrollAreaConditionContent* content = new ScrollAreaConditionContent(scrollArea);

    connect(content, &ScrollAreaConditionContent::widgetInvisible, scrollArea, [scrollArea](QWidget* childWidget)
            {
                int horScrollBarValue = scrollArea->horizontalScrollBar()->value();
                scrollArea->ensureWidgetVisible(childWidget);
                scrollArea->horizontalScrollBar()->setValue(horScrollBarValue);
            });

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
        return conditionPageDataCheck(1);
    case 2:
        return conditionPageDataCheck(2);
    case 3:
        return fourthPageDataCheck();
    default:
        Q_ASSERT_X(false, "ConditionLevelCreate::checkDataValidation", "undefined page number");
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
    QString rowsCount = QString::number(ui->rows->value());
    if (!Checker::checkSize(rowsCount))
    {
        ui->rows->setStyleSheet(Styles::spinBoxEr());
        utils::sendMessage(m_errorWindowName, errorSizeMessage);
        return false;
    }
    ui->rows->setStyleSheet(Styles::spinBoxNorm());

    QString columnCount = QString::number(ui->columns->value());
    if (!Checker::checkSize(columnCount))
    {
        ui->columns->setStyleSheet(Styles::spinBoxEr());
        utils::sendMessage(m_errorWindowName, errorSizeMessage);
        return false;
    }
    ui->columns->setStyleSheet(Styles::spinBoxNorm());

    return true;
}

bool ConditionLevelCreate::nameCheck()
{
    QString newName = ui->levelName->text();
    if (newName.isEmpty() || m_levelsName.contains(newName))
    {
        ui->levelName->setStyleSheet(Styles::lineEditEr());
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
    ui->levelName->setStyleSheet(Styles::lineEditNorm());
    return true;
}

bool ConditionLevelCreate::conditionPageDataCheck(int curPageIndex)
{
    int maxSize = curPageIndex == 1 ? ui->columns->value() : ui->rows->value();
    int viewSize = curPageIndex == 1 ? m_linesContents->getViewSize() : m_columnsContents->getViewSize();
    QVector<ConditionElement*>& conditions = curPageIndex == 1 ? m_linesContents->getConditions() : m_columnsContents->getConditions();

    for (int i = 0; i < viewSize; ++i)
    {
        ConditionElement* cond = conditions[i];
        QString line = cond->getData();

        std::shared_ptr<bool> hasCriticalError = std::make_shared<bool>(false);
        DataInformation::conditionLine condition = LevelData::createConditionFromStr(line, hasCriticalError);

        if (*hasCriticalError == true)
        {
            cond->setStyleSheetLineEdit(Styles::lineEditEr());
            return false;
        }

        if (!Checker::checkConditionLine(condition, maxSize))
        {
            cond->setStyleSheetLineEdit(Styles::lineEditEr());
            return false;
        }

        cond->setStyleSheetLineEdit(Styles::lineEditNorm());
    }

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

        QVector<ConditionElement*>& conds = m_linesContents->getConditions();
        for (int i = 0; i < rowsCount; ++i)
        {
            conds[i]->setStyleSheetLineEdit(Styles::lineEditNorm());
        }
    }

    int columnCount = ui->columns->value();
    if (columnCount != m_columnsContents->getViewSize())
    {
        m_columnsContents->updateContent(columnCount);

        QVector<ConditionElement*>& conds = m_columnsContents->getConditions();
        for (int i = 0; i < columnCount; ++i)
        {
            conds[i]->setStyleSheetLineEdit(Styles::lineEditNorm());
        }
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

std::vector<DataInformation::conditionLine> ConditionLevelCreate::getConditions(const QVector<ConditionElement*>& data, int viewSize) const
{
    std::vector<DataInformation::conditionLine> conditionsList;
    conditionsList.reserve(viewSize);

    for (int i = 0; i < viewSize; ++i)
    {
        const ConditionElement* cond = data[i];
        QString line = cond->getData();
        DataInformation::conditionLine condition = LevelData::createConditionFromStr(line);
        conditionsList.push_back(condition);
    }

    return conditionsList;
}

std::vector<DataInformation::additionCondLine> ConditionLevelCreate::getAdditions(const QVector<ConditionElement*>& data, int viewSize) const
{
    std::vector<DataInformation::additionCondLine> condition;
    condition.reserve(viewSize);

    for (int i = 0; i < viewSize; ++i)
    {
        const ConditionElement* cond = data[i];

        QStringList values;
        QString line = cond->getData();
        FileParser::getLevelData(line, values);

        DataInformation::additionCondLine oneAdditionalCondition;
        for (int i = 0; i < 3; ++i)
        {
            oneAdditionalCondition[i] = values[i].toInt();
        }

        condition.push_back(oneAdditionalCondition);
    }

    return condition;
}
