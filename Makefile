WORKING_DIR			?= $(shell pwd)

.DEFAULT_GOAL := help

down: ## clean and create folders to build
	@rm -r build
	@rm -r sdk
	@cmake -B build .

	
build: ## build project
	@cd $(WORKING_DIR)/build
	@make

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: down build help