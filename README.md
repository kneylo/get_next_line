This project has been created as part of the 42 curriculum by [nekreter](https://github.com/kneylo)

# Get Next Line

### [Description](#description) · [Content](#content) · [Instructions](#instructions) · [Resources](#resources) · [Testing](#testing)

## Description

This project is the second project of my cursus at 42 Lausanne. The goal is to create a function capable of reading a file descriptor one line at a time.

The main challenge of this project is to correctly handle the data read from the file while keeping track of the part that has not yet been returned. The function therefore needs to keep a **static buffer**, called `stash`, between calls.

The project also introduces the use of the `read` function and requires careful management of dynamically allocated memory.

The main function of the project is:

```c
char	*get_next_line(int fd);
```

Each call to `get_next_line` returns the next line of the file, including the `\n` character when one is present.

When there are no more lines to read, the function returns `NULL`.

## Content

I divided the project into two different categories.

| Categories | Functions |
| --- | --- |
| Main function | `get_next_line` |
| Utility functions | `ft_strlen` `include_nl` `ft_strjoin` `ft_substr` `free_needed` |

The project is composed of three source files and one header:

- `get_next_line.c` - contains the main `get_next_line` function and the functions responsible for reading and extracting lines.
- `get_next_line_utils.c` - contains the utility functions used to manipulate strings and manage memory.
- `get_next_line.h` - contains the includes, `BUFFER_SIZE` definition and function prototypes.

### How it works

The implementation uses a static variable called `stash` to keep data between calls to `get_next_line`.

The general process is:

1. Allocate a buffer of `BUFFER_SIZE + 1` bytes.
2. Read from the file descriptor with `read`.
3. Add the newly read data to `stash`.
4. Continue reading until a `\n` is found or the end of the file is reached.
5. Extract the next line from `stash`.
6. Keep the remaining data in `stash` for the next call.
7. Return the extracted line.

This allows the function to handle cases where a single `read` does not contain a complete line, as well as cases where one `read` contains several lines.

### Buffer size

The amount of data read at each iteration is controlled by `BUFFER_SIZE`.

The project defines a default value in the header:

```c
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif
```

It is also possible to change the value when compiling, for example:

```bash
cc -D BUFFER_SIZE=42 ...
```

A different `BUFFER_SIZE` should not change the expected behaviour of `get_next_line`.

## Instructions

If you want to use this `get_next_line`, you'll need to start by cloning the repo and compiling the files together with your own program.

Clone the repository:

```bash
git clone https://github.com/kneylo/get_next_line.git
cd get_next_line
```

You can then compile the project together with a test file.

For example:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=5 main.c get_next_line.c get_next_line_utils.c
```

You can change the `BUFFER_SIZE` to test different situations:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 main.c get_next_line.c get_next_line_utils.c
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1000 main.c get_next_line.c get_next_line_utils.c
```

The function can then be used like this:

```c
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}

	close(fd);
	return (0);
}
```

The function takes a file descriptor as its only argument:

```c
char	*get_next_line(int fd);
```

and returns:

- The next line from the file.
- The line including `\n` if a newline is present.
- The last line even if it does not end with `\n`.
- `NULL` when there is nothing left to read or when an error occurs.

## Resources

My main sources of information on the web are some github of my peers and theses links below, AI was used more for a directive line or to find other way to attack the problem, never to write code except for some part of the readme.	 

[gitbook 42](https://42-cursus.gitbook.io/guide)

[ADD SOURCE HERE]

[ADD SOURCE HERE]

## Testing

First I tested the function myself using different text and different `BUFFER_SIZE` values.

Then I call other people to talk about the project, asking advices, compared how we did it and compared ourselves. 