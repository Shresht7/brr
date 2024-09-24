# `brr`

Writes stuff to the console like a typewriter!

This project is a command-line application written in C that simulates a typewriter effect when printing text to the console. The program types out the text with variable speed, adding a pause after certain characters to mimic the behavior of a typewriter. This is my first time using C in a proper project.

## Usage

```
brr [OPTIONS]
```

### Options

- `-c, --cpm <value>`: Characters per Minute (default: 500)
- `-v, --variance <value>`: The variance in the CPM speed. (default: 250)
- `-p, --pause <value>`: Adjust the pause duration multiplier (default: 2.0)
- `-h, --help`: Show the help message
- `-V, --version`: Show the version number

### Examples

```
git log | brr 
```

---

## 📄 License

This project is licensed under the [MIT License](./LICENSE)
