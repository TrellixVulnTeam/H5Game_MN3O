.PHONY: clean All

All:
	@echo ----------Building project:[ Recast - Debug ]----------
	@"$(MAKE)" -f "Recast.mk"
clean:
	@echo ----------Cleaning project:[ Recast - Debug ]----------
	@"$(MAKE)" -f "Recast.mk" clean
