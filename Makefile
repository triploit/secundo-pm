OBJ = sht2.o
CC = g++

compile: $(OBJ)
	@echo [CPP] Link SECPM...
	@$(CC) -fpermissive  -lreadline -lcurl -W -o secpm secpm.o
	@echo [CPP] Finished!
	@echo "–––––––––––––––––––––––––––"
	@rm sht2.o

sht2.o:
	@echo [CPP] Compile SECPM...
	@$(CC) -fpermissive -lreadline -lcurl -W -c main.cpp -o secpm.o
	@echo [CPP] Finished!
	@echo "–––––––––––––––––––––––––––"
