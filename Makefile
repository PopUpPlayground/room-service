all:
	platformio run -e teensy32

game:
	platformio run -e roomservice

install:
	platformio run -e roomservice --target upload

clean:
	rm -rf .pioenvs

test:	always
	platformio test -e local

monitor:
	platformio device monitor

always:
