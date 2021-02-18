# asplit

Written by Deven Blake; public domain.

The current upstream URL for this program is https://github.com/devenblake/asplit.

**Manual page corrections and additions are very welcome, I'm new to writing them.**

This program is very likely redundant to awk(1).
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

asplit compiles to around 16K with gcc 10.2.0. tcc compiles it to around 5.4K.

## "Maximum line length possibly exceeded"

This happens when lines received exceed `LINEM`-1 characters, `LINEM` being a constant defined near the start of the program.

You're welcome to change `LINEM` to a higher value (by default it's 1024) however this may cause asplit to use more memory.
When the maximum line length is exceeded asplit will still operate on the first `LINEM`-1 characters presented so most of the time there probably won't be any issue.

