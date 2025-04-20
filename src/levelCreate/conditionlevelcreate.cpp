#include "conditionlevelcreate.h"
#include "ui_conditionlevelcreate.h"

ConditionLevelCreate::ConditionLevelCreate(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::ConditionLevelCreate)
{
    ui->setupUi(this);
    ui->buttonNext->setFocus();
    ui->stackedWidget->setCurrentIndex(0);

    m_sections.reserve(ui->sectionsLayout->rowCount());
    for (int i = 0; i < ui->sectionsLayout->rowCount(); ++i)
    {
        m_sections.push_back(static_cast<QLabel*>(ui->sectionsLayout->itemAtPosition(i, 0)->widget()));
    }

    connectInitialization();
}

void ConditionLevelCreate::connectInitialization()
{
    connect(ui->buttonCancel, &QPushButton::clicked, this, &ConditionLevelCreate::reject);
    connect(ui->buttonBack, &QPushButton::clicked, this, &ConditionLevelCreate::backClicked);
    connect(ui->buttonNext, &QPushButton::clicked, this, &ConditionLevelCreate::nextClicked);
}

ConditionLevelCreate::~ConditionLevelCreate()
{
    delete ui;
}

void ConditionLevelCreate::backClicked()
{
    int oldIndex = ui->stackedWidget->currentIndex();
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
    int countPage = ui->stackedWidget->count();
    if (oldIndex == countPage - 1)
    {
        QDialog::accept();
        return;
    }

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
