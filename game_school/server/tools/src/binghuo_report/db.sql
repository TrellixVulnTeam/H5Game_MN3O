CREATE  TABLE `binghuo_report`.`report` (
  `id` BIGINT NOT NULL AUTO_INCREMENT ,
  `date` INT NOT NULL ,
  `time` VARCHAR(24) NOT NULL ,
  `agent` VARCHAR(20) NOT NULL ,
  `userid` VARCHAR(40) NOT NULL ,
  `uuid` VARCHAR(60) NOT NULL ,
  `server` VARCHAR(20) NOT NULL ,
  `stage` INT NOT NULL ,
  `detail_stage` INT NULL ,
  `filename` VARCHAR(128) NULL ,
  `desc` VARCHAR(128) NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `userid` (`userid` ASC) ,
  INDEX `uuid` (`uuid` ASC) )
DEFAULT CHARACTER SET = big5
COLLATE = big5_chinese_ci;
