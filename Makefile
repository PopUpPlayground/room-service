all:
	platformio run

install:
	platformio run --target upload

clean:
	rm -rf .pioenvs
