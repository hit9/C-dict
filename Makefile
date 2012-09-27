all:
	@gcc test.c dict.c -o test -g

test:all
	@touch test.log
	@env MALLOC_TRACE=test.log ./test
	@echo "memory leaks check result:"
	@mtrace test test.log
clean:
	@rm test test.log
