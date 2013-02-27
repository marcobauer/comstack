
all:	
	cd build/fat; make 
	cd build/slim; make 

clean:
	cd build/fat; make clean
	cd build/slim; make clean
	
build:
#	mkdir -p build/fat
#	mkdir -p build/slim	
#	cd build/fat; cmake ../..
#	cd build/slim; cmake ../.. -DSLIM=1
	
	mkdir -p unittest/build/fat
	mkdir -p unittest/build/slim
	cd unittest/build/fat; cmake ../..
	cd unittest/build/slim; cmake ../.. -DSLIM=1

cleanup:
	rm -rf 	build || true
	rm -rf  unittest/build || true
	rm -rf  lib || true
	
test:
	rm unittest/slim-test-run || true
	rm unittest/fat-test-run || true
	cd unittest/build/fat; make
	cd unittest/build/slim; make
	/unittest/fat-test-run
	/unittest/slim-test-run
	