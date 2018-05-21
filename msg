Program usage: ./surykatki <mode> {parameters}

Modes:
	-m1 : 
		Get one set of data from stdin, solve and print result to stdout.
		Required parameters: none
	-m2 :
		Generate one set of data, solve and print result to stdout.
		Required parameters: -n
	-m3 :
		Generate and solve multiple sets of data.
		Analyze complexity and compare it with expected complexity.
		Print table of results to stdout.
		Required parameters: -n, -k, -step, -r
	-gen :
		Generate one set of data and print to stdout.
		Required parameters: -n

Parameters:
	-n : 
		Number of crocodiles. Also determines the size of a river.
		Example: -n500
	-k :
		How many times to increment the number of crocodiles.
		Example: -k20
	-step :
		How much to increment the number of crocodiles with every iteration.
		Example: -step100
	-r :
		Number of various data sets to generate for every number of crocodiles.
		Example: -r10
	<< :
		Redirect stdin to file.
		Example: <<in.txt
	>> :
		Redirect stdout to file.
		Example: >>out.txt

	