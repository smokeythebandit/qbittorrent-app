TEMPLATE = subdirs

SUBDIRS += UserInterface \
           Backend

UserInterface.depends = Backend
