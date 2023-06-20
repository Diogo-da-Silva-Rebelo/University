-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema traffic_db
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema traffic_db
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `traffic_db` ;
USE `traffic_db` ;

-- -----------------------------------------------------
-- Table `traffic_db`.`geocoded_waypoints`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `traffic_db`.`geocoded_waypoints` (
  `id_geocoded_waypoints` INT NOT NULL AUTO_INCREMENT,
  `geocoder_status` VARCHAR(45) NULL,
  `place_id` VARCHAR(45) NULL,
  PRIMARY KEY (`id_geocoded_waypoints`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `traffic_db`.`routes`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `traffic_db`.`routes` (
  `id_routes` INT NOT NULL AUTO_INCREMENT,
  `bounds_ne_lat` FLOAT NULL,
  `bounds_ne_lon` FLOAT NULL,
  `bounds_sw_lat` FLOAT NULL,
  `bounds_sw_lon` FLOAT NULL,
  `bounds_nw_lat` FLOAT NULL,
  `bounds_nw_lon` FLOAT NULL,
  `bounds_se_lat` FLOAT NULL,
  `bounds_se_lon` FLOAT NULL,
  PRIMARY KEY (`id_routes`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `traffic_db`.`legs`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `traffic_db`.`legs` (
  `id_legs` INT NOT NULL AUTO_INCREMENT,
  `distance_text` VARCHAR(45) NOT NULL,
  `distance_value` INT NOT NULL,
  `duration_text` VARCHAR(45) NOT NULL,
  `duration_value` INT NOT NULL,
  `end_address` VARCHAR(255) NOT NULL,
  `end_location_lat` FLOAT NOT NULL,
  `end_location_lon` FLOAT NOT NULL,
  `start_address` VARCHAR(255) NOT NULL,
  `start_location_lat` FLOAT NOT NULL,
  `start_location_lon` FLOAT NOT NULL,
  `id_routes` INT NOT NULL,
  PRIMARY KEY (`id_legs`),
  INDEX `fk_legs_routes_idx` (`id_routes` ASC) VISIBLE,
  CONSTRAINT `fk_legs_routes`
    FOREIGN KEY (`id_routes`)
    REFERENCES `traffic_db`.`routes` (`id_routes`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `traffic_db`.`steps`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `traffic_db`.`steps` (
  `id_steps` INT NOT NULL AUTO_INCREMENT,
  `distance_text` VARCHAR(45) NOT NULL,
  `distance_value` INT NOT NULL,
  `duration_text` VARCHAR(45) NOT NULL,
  `duration_value` INT NOT NULL,
  `end_location_lat` FLOAT NOT NULL,
  `end_location_lon` FLOAT NOT NULL,
  `html_instructions` VARCHAR(255) CHARACTER SET 'utf8mb4' COLLATE 'utf8mb4_general_ci' NOT NULL,
  `maneuver` VARCHAR(50) NOT NULL,
  `polyline_points` VARCHAR(255) NOT NULL,
  `start_location_lat` FLOAT NOT NULL,
  `start_location_lon` FLOAT NOT NULL,
  `travel_mode` VARCHAR(50) NOT NULL,
  `id_legs` INT NOT NULL,
  PRIMARY KEY (`id_steps`),
  INDEX `fk_steps_legs1_idx` (`id_legs` ASC) VISIBLE,
  CONSTRAINT `fk_steps_legs1`
    FOREIGN KEY (`id_legs`)
    REFERENCES `traffic_db`.`legs` (`id_legs`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `traffic_db`.`speed_entry`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `traffic_db`.`speed_entry` (
  `id_speed_entry` INT NOT NULL AUTO_INCREMENT,
  `speed_value` INT NOT NULL,
  `speed_unit` VARCHAR(10) NOT NULL,
  `level` INT NOT NULL,
  `probability` FLOAT NOT NULL,
  `id_legs` INT NOT NULL,
  PRIMARY KEY (`id_speed_entry`, `id_legs`),
  INDEX `fk_speed_entry_legs1_idx` (`id_legs` ASC) VISIBLE,
  CONSTRAINT `fk_speed_entry_legs1`
    FOREIGN KEY (`id_legs`)
    REFERENCES `traffic_db`.`legs` (`id_legs`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `traffic_db`.`speed_sources`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `traffic_db`.`speed_sources` (
  `id_speed_sources` INT NOT NULL AUTO_INCREMENT,
  `value` INT NOT NULL,
  `id_speed_entry` INT NOT NULL,
  `id_legs` INT NOT NULL,
  `last_updated` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id_speed_sources`, `id_speed_entry`, `id_legs`),
  INDEX `fk_speed_sources_speed_entry1_idx` (`id_speed_entry` ASC, `id_legs` ASC) VISIBLE,
  CONSTRAINT `fk_speed_sources_speed_entry1`
    FOREIGN KEY (`id_speed_entry` , `id_legs`)
    REFERENCES `traffic_db`.`speed_entry` (`id_speed_entry` , `id_legs`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `traffic_db`.`via_waypoints`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `traffic_db`.`via_waypoints` (
  `id_via_waypoints` INT NOT NULL,
  `location_lat` FLOAT NULL,
  `location_lon` FLOAT NULL,
  `waypoint_order_value` INT NULL,
  PRIMARY KEY (`id_via_waypoints`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `traffic_db`.`routes_has_geocoded_waypoints`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `traffic_db`.`routes_has_geocoded_waypoints` (
  `id_routes` INT NOT NULL,
  `id_geocoded_waypoints` INT NOT NULL,
  PRIMARY KEY (`id_routes`, `id_geocoded_waypoints`),
  INDEX `fk_routes_has_geocoded_waypoints_geocoded_waypoints1_idx` (`id_geocoded_waypoints` ASC) VISIBLE,
  INDEX `fk_routes_has_geocoded_waypoints_routes1_idx` (`id_routes` ASC) VISIBLE,
  CONSTRAINT `fk_routes_has_geocoded_waypoints_routes1`
    FOREIGN KEY (`id_routes`)
    REFERENCES `traffic_db`.`routes` (`id_routes`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_routes_has_geocoded_waypoints_geocoded_waypoints1`
    FOREIGN KEY (`id_geocoded_waypoints`)
    REFERENCES `traffic_db`.`geocoded_waypoints` (`id_geocoded_waypoints`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
