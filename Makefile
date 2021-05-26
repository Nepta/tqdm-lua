tqdm.so: tqdm.cpp tqdm.h hue.h sol.hpp
	g++ -Wall -Werror -DSOL_ALL_SAFETIES_ON -g $(CFLAGS) $(LIBFLAG) -I$(LUA_INCDIR) $< -o $@

install: tqdm.so
	cp $< $(LIBDIR)

clean:
	rm tqdm.so
