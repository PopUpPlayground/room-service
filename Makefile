all:
	platformio run -e teensy32

install:
	platformio run -e teensy32 --target upload

clean:
	rm -rf .pioenvs

test:	always
	platformio test -e local

monitor:
	platformio device monitor

always:
