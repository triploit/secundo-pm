OBJ = secpm.o
CC = g++

compile: $(OBJ)
	@echo [CPP] Link SECPM...
	@$(CC) -fpermissive -static -W -o secpm secpm.o -w
	@echo [CPP] Finished!
	@echo "–––––––––––––––––––––––––––"
	@rm secpm.o

secpm.o:
	@echo [CPP] Compile SECPM...
	@$(CC) -static -W -c main.cpp -o secpm.o -w
	@echo [CPP] Finished!
	@echo "–––––––––––––––––––––––––––"
