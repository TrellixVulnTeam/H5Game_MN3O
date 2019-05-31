.PHONY: clean All

All:
	@echo ----------Building project:[ RecastPort - Debug ]----------
	@"$(MAKE)" -f "RecastPort.mk"
clean:
	@echo ----------Cleaning project:[ RecastPort - Debug ]----------
	@"$(MAKE)" -f "RecastPort.mk" clean
