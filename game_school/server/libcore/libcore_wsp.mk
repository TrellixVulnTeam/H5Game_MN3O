.PHONY: clean All

All:
	@echo ----------Building project:[ libcore - Debug ]----------
	@"$(MAKE)" -f "libcore.mk"
clean:
	@echo ----------Cleaning project:[ libcore - Debug ]----------
	@"$(MAKE)" -f "libcore.mk" clean
