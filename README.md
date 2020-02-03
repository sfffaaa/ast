Follow [this link for algorithm](https://ruslanspivak.com/lsbasi-part7/)

### Environment
Mac OS: 10.15.2

### Dependency
Install [gtest](https://github.com/iat-cener/tonatiuh/wiki/Installing-Google-Test-For-Mac)

### Test
1. Test case for functionality
2. Valgrind for memory checking
3. Coverage
```
File 'interpreter.cpp'
Lines executed:100.00% of 6
File 'lexer.cpp'
Lines executed:97.78% of 45
File 'parser.cpp'
Lines executed:96.72% of 61
```

### TODO
1. Cannot call parser.parse twice. However, I don't want to fix this.
