# sam

Some code for working with sam and bam files

[![DOI](https://www.zenodo.org/badge/173795585.svg)](https://www.zenodo.org/badge/latestdoi/173795585)

## [sam_len](sam_len.cpp)

This is a simple filter that reads a sam/bam file and filters based on the alignment length. You need to make sam_len.cpp with the command:

```
g++ -o sam_len -Ihtslib -Lhtslib  sam_len.cpp  /usr/lib/x86_64-linux-gnu/libhts.a -lz -lpthread -lcurl -lbz2 -llzma -lcurl -lcrypto
```

Then, you can use this with the command:

```bash
./sam_len 200  ERR1097474.bam filtered.bam
```

The parameters are:

```bash
Usage: ./sam_len len in.bam out.bam mode
	len is the length to filter alignments on
	in.bam is the bam file to read
	out.bam is the bam file to write
	mode is one of Q (Query length) or R (Reference length). Default is Query.
```

You can add an optional 4<sup>th</sup> parameter that will allow you to determine whether to the use the <em>R</em>eference or <em>Q</em>uery to determine the length.


## Alternate installation

If the hts and sam libraries are not installed system wide, you might try this approach to installing sam_len:

```
module load samtools/1.9
module load htslib/1.5
export LIBRARY_PATH=/path/to/samtools/1.9/lib:/path/to/samtools/1.9/htslib-1.9/lib:$LIBRARY_PATH
cp /path/to/samtools/1.9/lib/libbam.a .
g++ -o sam_len -Ihtslib -Lhtslib -lhts -L/path/to/bin/sam -lbam sam_len.cpp
```



