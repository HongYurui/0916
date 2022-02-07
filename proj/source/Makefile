cc = g++
prom = calc
obj = main.o time.o

$(prom): $(obj)
	$(cc) -o $(prom) $(obj)

%.o: %.c
	$(cc) -c $< -o $@
clean:
	rm -rf $(obj) $(prom)

