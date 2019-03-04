#include <iostream>
#include <htslib/sam.h>

// this was taken from a couple of fora posts including http://seqanswers.com/forums/archive/index.php/t-51201.html




int main(int argc, char **argv) {
    if(argc < 4) {
        fprintf(stderr, "Usage: %s len in.bam out.bam mode\n", argv[0]);
        std::cerr << "\tlen is the length to filter alignments on" << std::endl;
        std::cerr << "\tin.bam is the bam file to read" << std::endl;
        std::cerr << "\tout.bam is the bam file to write" << std::endl;
        std::cerr << "\tmode is one of Q (Query length) or R (Reference length). Default is Query." << std::endl;
        exit(-1);
    }
    int len=atoi(argv[1]);

    if (argc > 4 && ('R' != *argv[4] && 'Q' != *argv[4])) {
        std::cerr << "Error: mode must be R for reference or Q for query not " << argv[2]  << std::endl;
        return 1;
    }

    auto f = sam_open(argv[2], "r");
    auto h = sam_hdr_read(f);
    auto t = bam_init1();

    auto o = sam_open(argv[3], "wb");
    int i = sam_hdr_write(o, h);

    while (sam_read1(f, h, t) >= 0)
    {
        auto id = std::string(h->target_name[0]);
        auto mapped = !(t->core.flag & BAM_FUNMAP);

        const auto cigar = bam_get_cigar(t);

        int alnlen = 0;
        int reflen = 0;
        for (int k = 0; k < t->core.n_cigar; k++)
        {
            const int op = bam_cigar_op(cigar[k]);
            const int ol = bam_cigar_oplen(cigar[k]);

            if (op == BAM_CMATCH || op == BAM_CINS || op == BAM_CEQUAL || op == BAM_CDIFF)
                alnlen += ol;
            if (op == BAM_CMATCH || op == BAM_CDEL || op == BAM_CREF_SKIP || op == BAM_CEQUAL || op == BAM_CDIFF)
                reflen += ol;
        }
        // std::cout << "Alignmnet len: " << alnlen << " Reference len: " << reflen << std::endl;

        if (argc > 4 && 'R' == *argv[4]) {
            if (reflen < len)
                continue;
        }
        else if (alnlen < len)
            continue;


        int i = sam_write1(o, h, t);
        if (i < 0)
            std::cerr << "There was an error writing to the file (but we don't know what to do about it)"
                      << std::endl;
    }

    sam_close(f);
    sam_close(o);
}