import QtQuick 2.9
import "Calculator"

Column {
    id: root
    CalculatorScreen {
        id: calcScreen
        height: parent.height * 0.3
        width: parent.width
    }
    CalculatorInput {
        id: calcInput
        height: parent.height - calcScreen.height
        width: parent.width
        onDigitPressed: {
            calcScreen.addChar(digit)
        }
        onSignChPressed: {
            if(calcScreen.text[0] === "-") {
                calcScreen.text = calcScreen.text.substring(1, calcScreen.text.length )
            } else {
                calcScreen.text = "-" + calcScreen.text
            }
        }
        onDotPressed: {
            calcScreen.addChar(".")
        }
        onPlusPressed: {
            journalModel.submitToNumber(calcScreen.text)
            journalModel.pressPlus()
            calcScreen.clear()
        }
        onMinusPressed: {
            journalModel.submitToNumber(calcScreen.text)
            journalModel.pressMinus()
            calcScreen.clear()
        }
        onMultiplyPressed: {
            journalModel.submitToNumber(calcScreen.text)
            journalModel.pressMultiply()
            calcScreen.clear()
        }
        onDividePressed: {
            journalModel.submitToNumber(calcScreen.text)
            journalModel.pressDivide()
            calcScreen.clear()
        }
        onCalculatePressed: {
            journalModel.submitToNumber(calcScreen.text)
            journalModel.pressCalculate()
            journalModel.reset() // resets the operand
            calcScreen.clear()
        }
    }
}
