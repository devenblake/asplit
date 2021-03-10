# asplit

Written by Deven Blake; public domain.

The current upstream URL for this program is https://github.com/devenblake/asplit.

**Manual page corrections and additions are very welcome, I'm new to writing them.**

This program is very likely redundant to other utilities.
I didn't make it to accomplish a new task, rather, to accomplish the task quickly in a way that was easy for me.

Consult the manpage and the code for specifics on how it works.
It's less than a hundred lines of mostly readable C.

## usage examples

`echo "foo bar baz" | asplit "bar" 1` returns `baz`. `echo "foo bar baz" | asplit "bar" 0` returns `foo`.

`echo "foo bar baz" | asplit "bar"` returns `1`. `echo "foo bar baz" | asplit "bar" $(echo "foo bar baz" | asplit "bar")` returns `baz`.

`for file in $(ls); do echo "$file" | asplit . $(echo "$file" | asplit .); done` will output all the file extensions in the current directory, in a hacky way.
**Many uses of asplit are hack-ish and not quite production-quality.** Keep this in mind.

## installation

`cc asplit.c -o asplit`

Alternatively (if you have a `make` utility installed)

`make`

And to install asplit system-wide

`make install`

## "Couldn't re-allocate memory"

The file fed into asplit was for some reason too big.
This file would have megabytes of text without a newline.
If your computer has plenty of memory and your text file isn't so big please file a bug so I can check it out.
