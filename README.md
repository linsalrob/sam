# sam

Some code for working with sam and bam files

## [sam_len](sam_len.cpp)

This is a simple filter that reads a sam/bam file and filters based on the alignment length. You need to make sam_len.cpp with the command:

```
g++ -o sam_len -Ihtslib -Lhtslib  sam_len.cpp  /usr/lib/x86_64-linux-gnu/libhts.a -lz -lpthread -lcurl -lbz2 -llzma -lcurl -lcrypto
```

Then, you can use this with the command:

```bash
./sam_len 200  ERR1097474.bam filtered.bam
```

You can add an optional 4<sup>th</sup> parameter that will allow you to determine whether to the use the <em>R</em>eference or <em>Q</em>uery to determine the length.