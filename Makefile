all: version
	platformio run -e teensy32

game: version
	platformio run -e roomservice

native: version
	platformio run -e native

install: version
	platformio run -e roomservice --target upload

clean:
	rm -rf .pioenvs
	rm -rf src/version.h

test:	always
	platformio test -e local

monitor:
	platformio device monitor

version:
	perl -Mautodie -e'my $$version = `git describe --tags`; chomp $$version; open($$fh,">","src/version.h"); print {$$fh} "#ifndef VERSION_H\n#define VERSION_H\n#define VERSION \"$$version\"\n#endif\n";'

always:
