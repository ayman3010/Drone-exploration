#!make

.DEFAULT_GOAL := help

ifeq ($(ARGS),)
ARGS := ""
endif

# ----------------------
# Setup locally
# ----------------------
.PHONY: setup-client
setup-client:
	@cd client && npm install

.PHONY: setup-server
setup-server:
	@bash ./server/tools/setup-venv.sh

.PHONY: setup
setup: setup-client setup-server ## install required node modules and python virtual environement
	@echo "----- setting up environement ------"

# ----------------------
# Start project locally
# ----------------------

.PHONY: start-client-local
start-client-local:
	@cd client && npm start

.PHONY: start-server-local
start-server-local:
	@cd server && . venv/bin/activate && cd src && flask run

# ----------------------
# Build Images
# ----------------------
.PHONY: build-client
build-client:
	@docker build -f client/Dockerfile.client -t client .

.PHONY: build-server
build-server:
	@docker build -f server/Dockerfile.server -t server .


# ----------------------
# Start on docker
# ----------------------

.PHONY: start
start:
	@docker compose -f docker-compose.yml up

.PHONY: down
down:
	@docker compose -f docker-compose.yml down -v

.PHONY: start-client
start-client:
	@docker run -p 127.0.0.1:4200:4200 client

.PHONY: start-server
start-server:
	@docker run -p 6001:6001 server

.PHONY: down-client
down-client:
	@echo "not implemented yet"

.PHONY: down-server
down-server:
	@echo "not implemented yet"


# ----------------------
# Debug on docker
# ----------------------

.PHONY: debug-client
debug-client:
	@docker exec -it inf3995-106-client-server-1 bash

.PHONY: debug-server
debug-server:
	@docker exec -it inf3995-106-web-server-1 bash


.PHONY: help
help: 
	@echo "Please specify a makefile rule"
