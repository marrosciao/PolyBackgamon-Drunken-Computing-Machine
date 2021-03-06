#Flags, Libraries and Includes
# -fdiagnostics-color=auto
export CFLAGS        += -std=c11 -Wall -Wextra -Wshadow -pedantic -pipe
# -fsanitize=address
export CFLAGS_DEBUG  += -Og -g
export CFLAGS_PROD   += -O2 -s -DNDEBUG -DLOG_LVL=NONE
export CPPFLAGS      += -MMD -MP -I include
export LDFLAGS       +=
export LDLIBS        +=

.PHONY: interface strategy clean doc

all: interface strategy

interface strategy:
	@$(MAKE) -C $@

clean:
	@$(MAKE) -C strategy clean
	@$(MAKE) -C interface clean
	@rm -rf doc

doc:
	@doxygen Doxyfile
