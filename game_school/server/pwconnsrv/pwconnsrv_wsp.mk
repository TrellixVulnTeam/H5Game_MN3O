.PHONY: clean All

All:
	@echo ----------Building project:[ pwconnsrv - Debug ]----------
	@"$(MAKE)" -f "pwconnsrv.mk"
clean:
	@echo ----------Cleaning project:[ pwconnsrv - Debug ]----------
	@"$(MAKE)" -f "pwconnsrv.mk" clean
