OBJ = sht2.o
CC = g++

compile: $(OBJ)
	@echo [CPP] Link SECPM...
	@$(CC) -fpermissive -static -W -o secpm secpm.o
	@echo [CPP] Finished!
	@echo "–––––––––––––––––––––––––––"
	@rm secpm.o

sht2.o:
	@echo [CPP] Compile SECPM...
	@$(CC) -static -W -c main.cpp -o secpm.o
	@echo [CPP] Finished!
	@echo "–––––––––––––––––––––––––––"
