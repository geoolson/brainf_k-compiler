make:
	gcc -g -o gccbrain brain.c

clean:
	ls | grep -E 'out.c|a.out' | xargs -d"\n" rm

