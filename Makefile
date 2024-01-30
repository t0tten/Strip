strip:
	g++ Strip.cpp -o strp

clean:
	rm -rf ./test
	rm ./strp

build:
	rm -rf ./test
	mkdir test
	touch ./test/{1..5}
	touch ./test/{6..10}.busy

rename:
	find . -iname "*.busy" -exec ./strp {} .busy \;
