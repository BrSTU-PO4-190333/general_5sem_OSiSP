## Compile main.pdf

```bash
docker-compose run latex /bin/bash

cd /content/rep
make build
make build
```

Open [main.pdf](main.pdf).

Cleaning up the project:

```
make clean
exit
docker-compose down
```
