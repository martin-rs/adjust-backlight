all:
	cc -Wall -std=c17 adjust-brightness.c -o ${SCRIPTDIR}/system/br

clean:
	rm -rf ${SCRIPTDIR}/system/br
