#include "conditionlevelcreate.h"
#include "ui_conditionlevelcreate.h"
#include "../utils.h"

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
    if (newIndex < 0)
    {
        return;
    }
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
    if (newIndex < countPage)
    {
        if (newIndex == countPage - 1)
        {
            ui->buttonNext->setText("Finish");
        }

        ui->buttonBack->setEnabled(true);
        ui->stackedWidget->setCurrentIndex(newIndex);
        setSectionsFont(newIndex, ButtonClicked::next);
    }
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
    QString newName = ui->levelName->text();
    if (newName.isEmpty() || m_levelsName.contains(newName))
    {
        ui->labelLevelName->setStyleSheet(m_errorBack);
        if (newName.isEmpty())
        {
            utils::sendMessage(tr("Error"), tr("Level name is empty!"));
        }
        else
        {
            utils::sendMessage(tr("Error"), tr("Name already exist!"));
        }
        return false;
    }
    ui->labelLevelName->setStyleSheet(m_normalBack);

    if (ui->rows->value() <= 0)
    {
        ui->labelRowCount->setStyleSheet(m_errorBack);
        utils::sendMessage(tr("Error"), tr("Invalid sizes!"));
        return false;
    }
    ui->labelRowCount->setStyleSheet(m_normalBack);

    if (ui->columns->value() <= 0)
    {
        ui->labelColumCount->setStyleSheet(m_errorBack);
        utils::sendMessage(tr("Error"), tr("Invalid sizes!"));
        return false;
    }
    ui->labelColumCount->setStyleSheet(m_normalBack);

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
