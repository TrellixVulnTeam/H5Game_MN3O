.PHONY: clean All

All:
	@echo ----------Building project:[ utf_bom_convert - Debug ]----------
	@"mingw32-make.exe"  -j 4 -f "utf_bom_convert.mk"
clean:
	@echo ----------Cleaning project:[ utf_bom_convert - Debug ]----------
	@"mingw32-make.exe"  -j 4 -f "utf_bom_convert.mk" clean
