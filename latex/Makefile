template.pdf: template.tex main
	./main
	xelatex -shell-escape template.tex
	xelatex -shell-escape template.tex

template.tex: main

main: main.cpp
	g++ main.cpp -o main

clean:
	rm template.* main
