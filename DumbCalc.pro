TEMPLATE = subdirs

SUBDIRS += \
    src \
    calcLib

CONFIG(debug, debug|release) {
#    SUBDIRS += tests
}
