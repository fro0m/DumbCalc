#include <QColor>
#include <QQueue>
#include <QChar>
#include "journalmodel.h"
#include "core/threadmanager.h"
#include "DataTypes/result.h"
#include <QDebug>


JournalModel::JournalModel(QObject *parent)
    : QAbstractListModel(parent)
{
    connect(&queuesWatcher, &QueuesWatcher::requestsSizeChanged, this, &JournalModel::requestsSizeChanged);
    connect(&queuesWatcher, &QueuesWatcher::resultsSizeChanged, this, &JournalModel::resultsSizeChanged);
    connect(&queuesWatcher, &QueuesWatcher::resultIsReady, [this](const Result &result) {
        qDebug() << "result is " << result.m_result;
        switch(result.m_errorCode) {
        case CalcLib::Div0:
            addMessage("Деление на ноль запрещено", JournalItem::Error);
            break;
        case CalcLib::WrongTypeWork:
            addMessage("Неизвестная операция", JournalItem::Error);
            break;
        case CalcLib::Ok:
            addMessage("Результат вычисления " + QString::number(result.m_result), JournalItem::Result);
            break;
        }
    });
    addMessage("Вас приветствует калькулятор.", JournalItem::Request);
}

int JournalModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    return m_data.size();
}

QVariant JournalModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    Q_ASSERT(index.row() >= 0);
    auto row = index.row();
    switch (role) {
    case Text:
        return m_data.at(row).text;
    case Color: {
        using Rls = JournalItem::ItemType;
        switch (m_data.at(row).itemType) {
        case Rls::Request:
            return QColor(0, 0, 255);
        case Rls::Result:
            return QColor(0, 255, 0);
        default:
            return QColor(255, 0, 0);
        }
    }
    case ErrorType:
        return m_data.at(row).errorCode;
    default:
        Q_ASSERT_X(false, Q_FUNC_INFO, "wrong data role is requested");
        return QVariant();
    }
}

void JournalModel::pressMinus()
{
    if(currentOperand == &m_currentTask.m_operandA) {
        m_currentTask.m_typeWork = CalcLib::Subtraction;
        currentOperand = &m_currentTask.m_operandB;
    } else {
        addMessage("Надо нажать равно", JournalItem::Error);
    }
}

void JournalModel::pressPlus()
{
    if(currentOperand == &m_currentTask.m_operandA) {
        m_currentTask.m_typeWork = CalcLib::Addition;
        currentOperand = &m_currentTask.m_operandB;
    } else {
        addMessage("Надо нажать равно или удалить", JournalItem::Error);
    }
}

void JournalModel::pressDivide()
{
    if(currentOperand == &m_currentTask.m_operandA) {
        m_currentTask.m_typeWork = CalcLib::Division;
        currentOperand = &m_currentTask.m_operandB;
    } else {
        addMessage("Надо нажать равно или удалить", JournalItem::Error);
    }
}

void JournalModel::pressMultiply()
{
    if(currentOperand == &m_currentTask.m_operandA) {
        m_currentTask.m_typeWork = CalcLib::Multiplication;
        currentOperand = &m_currentTask.m_operandB;
    } else {
        addMessage("Надо нажать равно или удалить", JournalItem::Error);
    }
}

void JournalModel::pressCalculate()
{
    if (currentOperand == &m_currentTask.m_operandB) {
        //        Task task = {CalcLib::Addition, 111, 223, 3, false};
        m_currentTask.m_operationsComplexityInSec = 10;
        QMetaObject::invokeMethod(&queuesWatcher, "submitTask",
                                  Q_ARG(Task, m_currentTask));
        QChar operation;
        switch(m_currentTask.m_typeWork) {
        case CalcLib::Addition:
            operation = '+';
            break;
        case CalcLib::Subtraction:
            operation = '-';
            break;
        case CalcLib::Division:
            operation = 0x00F7;
            break;
        case CalcLib::Multiplication:
            operation = 0x00D7;
            break;
        default:
            Q_ASSERT(false);

        }
        addMessage(QString("Считаем %1 %2 %3").arg(m_currentTask.m_operandA).arg(operation).arg(m_currentTask.m_operandB), JournalItem::Request);
    } else {
        addMessage("Подскажите, что вы хотите сделать.", JournalItem::Error);
    }
}

void JournalModel::submitToNumber(QString digit)
{
    *currentOperand = digit.toDouble();
}

void JournalModel::reset() {
    currentOperand = &m_currentTask.m_operandA;
}

void JournalModel::addJournalItem(const JournalItem &item)
{
    m_data.push_back(item);
}

void JournalModel::setTypeWork(CalcLib::TypeWork typeWork)
{
    if (m_currentTask.m_typeWork == typeWork)
        return;

    m_currentTask.m_typeWork = typeWork;
    emit typeWorkChanged(m_currentTask.m_typeWork);
}

void JournalModel::setOperandB(double operandB)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_currentTask.m_operandB, operandB))
        return;

    m_currentTask.m_operandB = operandB;
    emit operandBChanged(m_currentTask.m_operandB);
}

void JournalModel::setOperandA(double operandA)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_currentTask.m_operandA, operandA))
        return;

    m_currentTask.m_operandA = operandA;
    emit operandAChanged(m_currentTask.m_operandA);
}

void JournalModel::addMessage(const QString &text, JournalItem::ItemType itemType, CalcLib::ErrorCode errorCode)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.push_back({text, itemType, errorCode});
    endInsertRows();
}

QHash<int, QByteArray> JournalModel::roleNames() const
{
    return m_roleNames;
}

//QModelIndex JournalModel::index(int row, int column, const QModelIndex &parent) const
//{
//    Q_UNUSED(column)
//    int rowX = rowCount() - 1 - row;
//    void * ptr = static_cast<void *>(const_cast<JournalItem *>(&m_data.at(rowX)));
//    return createIndex(rowX, 0, ptr);
//}
