#ifndef JOURNALMODEL_H
#define JOURNALMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <QString>
#include "DataTypes/journalitem.h"
#include "DataTypes/task.h"
#include "calclib/calclib.h"
#include "Workers/queueswatcher.h"

class CalculatingThread;

/// serves GUI comands as well as provide Journal of operations
class JournalModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(double operandA READ operandA WRITE setOperandA NOTIFY operandAChanged)
    Q_PROPERTY(double operandB READ operandB WRITE setOperandB NOTIFY operandBChanged)
    Q_PROPERTY(CalcLib::TypeWork typeWork READ typeWork WRITE setTypeWork NOTIFY typeWorkChanged)
    // need for understanding if operands are already charged
    Q_PROPERTY(bool ready READ ready WRITE setReady NOTIFY readyChanged)

    Q_PROPERTY(int requestsSize READ requestsSize NOTIFY requestsSizeChanged)
    Q_PROPERTY(int resultsSize READ resultsSize NOTIFY resultsSizeChanged)
private:
    enum Roles {
        Text = Qt::UserRole,
        Color,
        ErrorType
    };
    Q_ENUM(JournalModel::Roles)
public: // Abstract Model interface
    explicit JournalModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
public: // task control
//    Q_INVOKABLE void pressDigit(int digit);
    Q_INVOKABLE void pressMinus();
    Q_INVOKABLE void pressPlus();
    Q_INVOKABLE void pressDivide();
    Q_INVOKABLE void pressMultiply();
    Q_INVOKABLE void pressCalculate();
    Q_INVOKABLE void submitToNumber(QString digit);
    Q_INVOKABLE void reset();
public: // journal items management
    void addJournalItem(const JournalItem &item);
public: // getters
    CalcLib::TypeWork typeWork() const
    {
        return m_currentTask.m_typeWork;
    }

    double operandB() const
    {
        return m_currentTask.m_operandB;
    }

    double operandA() const
    {
        return m_currentTask.m_operandA;
    }

    bool ready() const
    {
        return m_currentTask.m_ready;
    }

    int requestsSize() const
    {
        return queuesWatcher.requestsSize();
    }

    int resultsSize() const
    {
        return queuesWatcher.resultsSize();
    }

public slots:
    void setTypeWork(CalcLib::TypeWork typeWork);

    void setOperandB(double operandB);

    void setOperandA(double operandA);

    void setReady(bool ready);

signals:
    void typeWorkChanged(CalcLib::TypeWork typeWork);

    void operandBChanged(double operandB);

    void operandAChanged(double operandA);

    void readyChanged(bool ready);

    void requestsSizeChanged(int requestsSize);

    void resultsSizeChanged(int resultsSize);
private: // journal processing logic
    void addMessage(const QString &text, JournalItem::ItemType itemType, CalcLib::ErrorCode errorCode = CalcLib::Ok);
private: //current task data
    Task m_currentTask;
    double * currentOperand = &m_currentTask.m_operandA;
private: // data
    QVector<JournalItem> m_data;
    QueuesWatcher queuesWatcher; // need to delete ready flag, as we use ptr to operand
    QHash<int, QByteArray> m_roleNames {{Text, "text"},
                                        {Color, "color"},
                                        {ErrorType, "errorType"}
                                       };
};

#endif // JOURNALMODEL_H
