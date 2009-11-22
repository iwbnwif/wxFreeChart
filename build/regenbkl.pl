#!/usr/bin/perl -w
use strict;

#
# Regenerate bkl
#

my $bkl = "wxfreechart.bkl";

my $BKL;

my $srcs = `find ../src/ -name '*.cpp'`;
$srcs =~ s/\.\.\///g;

my $hdrs = `find ../include/ -name '*.h'`;
$hdrs =~ s/\.\.\///g;


my $in_comp_src;
my $in_comp_hdr;
my $is_comment;

my $bkl_content;

open BKL, "< ", $bkl or die "Cannot open $bkl: $!";
while (my $line = <BKL>) {
    chomp $line;

    if ($line =~ /<!--/) {
	$is_comment = 1;
    }
    
    if ($line =~ /-->/) {
	undef $is_comment;
    }

    if (!$is_comment) {
	if ($line =~ /<set var="COMP_SRC"/) {
	    $in_comp_src = 1;
	}
	elsif ($line =~ /<set var="COMP_HDR"/) {
	    $in_comp_hdr = 1;
	}
	elsif ($line =~ /<\/set/) {
	    if ($in_comp_src) {
		$bkl_content .= $srcs;
		undef $in_comp_src;
	    }
	    if ($in_comp_hdr) {
		$bkl_content .= $hdrs;
		undef $in_comp_hdr;
	    }
	}
	elsif ($in_comp_src || $in_comp_hdr) {
	    next;
	}
    }
    
    $bkl_content .= "$line\n";
}
close BKL;

system "mv $bkl $bkl.bak";

open BKL, "> ", $bkl or die "Cannot open $bkl: $!";
print BKL $bkl_content;
close BKL;
