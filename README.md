# Copyfile

Copy file data and/or metadata using copyfile(3) on macOS.

## Installation

### Prerequisites

- macOS 10.12 (Sierra) or later
- Xcode and the Command Line Tools installed

### From source

Clone the repository and navigate to the project directory:

```sh
git clone https://github.com/inopinatus/copyfile.git
cd copyfile
```

Compile and install:

```sh
make install
```

Now, you should be able to use `copyfile` from anywhere in your terminal. By default, files will be installed under `/usr/local`. You can adjust locations using the variables in the Makefile, e.g. `make install PREFIX=/opt`.

## Usage

```
copyfile src dst [flags...]
```

The arguments have the same meaning as those passed to the copyfile(3) library function. The **src** and **dst** are paths. The **flags** option accepts a list of space-separated strings matching those of the library call, and may be any of:

_acl stat xattr data security metadata all nofollow_src nofollow_dst nofollow excl move unlink pack unpack check clone clone_force verbose recursive data_sparse run_in_place preserve_dst_tracked_

See copyfile(3) for the documented meaning of these flags.

Note that only specified contents is copied. If no flags are given, then no contents will be copied, but the destination may be created if it does not already exist.

## Examples

1. Copy a file and its metadata:

```sh
copyfile file1.txt file2.txt all
```

2. Copy _only_ the metadata of one file to another, leaving the destination's data intact:

```sh
copyfile original.png revised.jpg metadata
```

3. Attempt to recursively clone a hierarchy, including metadata, with fallback to a sparse-aware regular copy:

```sh
copyfile ~/src ~/tmp/src.backup recursive data_sparse clone
```

## Exit Status

The copyfile utility exits with 0 on success, or >0 if an error occurs.

## Callbacks

The callback behaviours in the copyfile(3) library are not available through this utility.

## License

This version of copyfile is adapted directly from [test code](https://github.com/apple-oss-distributions/copyfile/blob/ed3f0a8bf8b6bac6838c92c297afcc826fec75f4/copyfile.c#L3479) included in [Apple OSS releases](https://opensource.apple.com/releases/), and therefore distributed under the Apple Public Source License.

## Contributing

Bug reports and pull requests are welcome on Github at https://github.com/inopinatus/copyfile
