TEMPLATE = subdirs

SUBDIRS += \
        Geltan \
        Test

Test.depends = Geltan
