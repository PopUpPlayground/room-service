all:
	platformio run -e teensylc

install:
	platformio run -e teensylc --target upload

clean:
	rm -rf .pioenvs

test:	always
	platformio test -e local

monitor:
	platformio device monitor

always:
