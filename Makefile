# Configuration
.PHONY: build-data-image build-app-image-master build-app-image-release build-deps-image dockerhub-login get-app-master-tag get-app-release-tag push-app-image push-deps-image push-data-image wipe-useless-images help
.DEFAULT_GOAL := help

BBOX ='-5.1972 8.3483 42.2646 51.1116' # France

build-data-image: ## Build Asgard data image with provided pbf (PBF_URL) and bbox for elevation data
	$(info Building Asgard data image)
	cd docker/asgard-data && \
	docker build --build-arg pbf_url="${PBF_URL}" --build-arg elevation_min_x_max_x_min_y_max_y="${BBOX}" -t navitia/asgard-data:${TAG} . --no-cache

build-app-image-master: ## Build Asgard app image from master
	$(info Building Asgard app image from master)
	docker build -f docker/asgard-app/Dockerfile -t navitia/asgard-app:${TAG} . --no-cache

build-app-image-release: ## Build Asgard app image from release
	$(info Building Asgard app image from release)
	docker build -f docker/asgard-app/Dockerfile -t navitia/asgard-app:${TAG} . --no-cache

build-deps-image: ## Build Asgard deps image
	$(info Building Asgard app image from master)
	docker build -f docker/asgard-build-deps/Dockerfile -t navitia/asgard-build-deps:${TAG} . --no-cache

dockerhub-login: ## Login Docker hub, DOCKERHUB_USER, DOCKERHUB_PWD, must be provided
	$(info Login Dockerhub)
	echo ${DOCKERHUB_PWD} | docker login --username ${DOCKERHUB_USER} --password-stdin

get-app-master-tag: ## Get master tag
	@echo "master"

get-app-release-tag: ## Get release version tag
	@[ -z "${TAG}" ] && (git describe --tags --abbrev=0 && exit 0) || echo ${TAG}

remove-build-deps-image: ## Remove navitia/asgard-build-deps if existent
	$(info Remove navitia/asgard-build-deps)
	docker rmi -f navitia/asgard-build-deps:latest || true    

push-app-image: ## Push app-image to dockerhub
	$(info Push app-image to Dockerhub)
	docker push navitia/asgard-app:${TAG}

push-deps-image: ## Push deps-image to dockerhub
	$(info Push deps-image to Dockerhub)
	docker push navitia/asgard-build-deps:${TAG}

push-data-image: ## Push data-image to dockerhub, TAG must be provided 
	$(info Push data-image to Dockerhub)
	docker push navitia/asgard-data:${TAG}

wipe-useless-images: ## Remove all useless images
	$(info Remove useless images)
	@./scripts/remove_asgard_and_dangling_images.sh

##
## Miscellaneous
##
help: ## Print this help message
	@grep -E '^[a-zA-Z_-]+:.*## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

