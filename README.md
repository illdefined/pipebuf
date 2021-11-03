## Synopsis

`pipebuf` is as a low‐overhead buffer for command pipelines.

## Usage

`pipebuf` reads from standard input and writes to standard output, buffering the data it passes through. The buffer
capacity can be adjusted by providing the size as a command line argument. If no size is provided, it will default to
1048576 (1 MiB).

At least one of standard input or standard output is required to be a pipe.

## Implementation notes

This tool relies on the Linux‐specific `splice(2)` system call.

Since the pipes themselves serve as buffers, the capacity is limited by the system’s maximum pipe size as set in
`/proc/sys/fs/pipe-max-size`.
