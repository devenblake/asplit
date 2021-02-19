SRC = asplit.c

include config.mk

all: asplit

asplit:
	@echo CC -o $@
	@${CC} -o $@ ${SRC}

clean:
	@echo cleaning
	@rm -f asplit

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f asplit ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/asplit
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@cp -f asplit.1 ${DESTDIR}${MANPREFIX}/man1/asplit.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/asplit.1

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/asplit
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/asplit.1

.PHONY: all clean install uninstall
