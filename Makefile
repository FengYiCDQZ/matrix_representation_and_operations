CC = g++ -std=c++17 
CC_FLAGS = -g -fopenmp

double_spmtx = xdbl_spmtx_vec
zplx_spmtx = xzplx_spmtx_vec

all: $(double_spmtx) $(zplx_spmtx)

$(double_spmtx): drv_spmtx_double.o 
	@echo "----- Building $(double_spmtx) -----"
	$(CC) $(CC_FLAGS) $^ -ltbb -o $@
	@echo

$(zplx_spmtx): drv_spmtx_zplx.o 
	@echo "----- Building $(zplx_spmtx) -----"
	$(CC) $(CC_FLAGS) $^ -ltbb -o $@
	@echo

%.o: ./src/%.cpp
	$(CC) $(CC_FLAGS) -Wall -c $< -o $@ 
%.o: ./src/%.cc
	$(CC) $(CC_FLAGS) -Wall -c $< -o $@
%.o : ./src/%.cu 
	$(CC) $(CC_FLAGS) -Wall -c $< -o $@

doc :
	doxygen Doxyfile

clean:
	rm -f *.o *.x x*
