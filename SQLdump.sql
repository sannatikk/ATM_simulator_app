-- MySQL dump 10.13  Distrib 8.0.34, for macos13 (arm64)
--
-- Host: mysql-25427c4-cashmate.a.aivencloud.com    Database: bank_automat
-- ------------------------------------------------------
-- Server version	8.0.30

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
SET @MYSQLDUMP_TEMP_LOG_BIN = @@SESSION.SQL_LOG_BIN;
SET @@SESSION.SQL_LOG_BIN= 0;

--
-- GTID state at the beginning of the backup 
--

SET @@GLOBAL.GTID_PURGED=/*!80000 '+'*/ '577f4ec8-ecd9-11ee-b369-82984fc0fa57:1-360';

--
-- Table structure for table `bank_account`
--

DROP TABLE IF EXISTS `bank_account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `bank_account` (
  `id_account` varchar(20) NOT NULL,
  `balance` decimal(10,2) NOT NULL,
  `credit_limit` decimal(10,2) NOT NULL,
  PRIMARY KEY (`id_account`),
  UNIQUE KEY `id_account_UNIQUE` (`id_account`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bank_account`
--

LOCK TABLES `bank_account` WRITE;
/*!40000 ALTER TABLE `bank_account` DISABLE KEYS */;
INSERT INTO `bank_account` VALUES ('FI2110000011111111',4047.24,0.00),('FI2130000033333333',2585.24,2000.00),('FI2150000055555555',6835.24,0.00),('FI2170000077777777',7635.24,9000.00),('FI2190000099999999',3765.24,0.00);
/*!40000 ALTER TABLE `bank_account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card`
--

DROP TABLE IF EXISTS `card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `card` (
  `id_card` varchar(20) NOT NULL,
  `pincode` varchar(255) NOT NULL,
  `is_combined` tinyint NOT NULL,
  PRIMARY KEY (`id_card`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
INSERT INTO `card` VALUES ('0600062E1F','$2a$10$B8EWH7hyRyOoFC4vba4qT.gc5.gCZiCOX5aCIEjZC7AjnzOijcTLm',0),('06000D5C69','$2a$10$4yM2faGIa.c/7bcRCaF05OfJF4/Ae7bF0pJaHeYUGXgq7bydxd6S6',1),('0B00320D2B','$2a$10$D3YDItP1.SjI4m8XzSCj2etXNKkkVtwt4v6jajU4CPicchl9eZqSi',0);
/*!40000 ALTER TABLE `card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card_account`
--

DROP TABLE IF EXISTS `card_account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `card_account` (
  `id_card_account` int NOT NULL AUTO_INCREMENT,
  `id_account` varchar(20) NOT NULL,
  `id_card` varchar(20) NOT NULL,
  PRIMARY KEY (`id_card_account`),
  UNIQUE KEY `id_card_account_UNIQUE` (`id_card_account`),
  UNIQUE KEY `id_account_UNIQUE` (`id_account`),
  KEY `id_card_idx` (`id_card`),
  CONSTRAINT `fk_id_account` FOREIGN KEY (`id_account`) REFERENCES `bank_account` (`id_account`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `fk_id_card` FOREIGN KEY (`id_card`) REFERENCES `card` (`id_card`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card_account`
--

LOCK TABLES `card_account` WRITE;
/*!40000 ALTER TABLE `card_account` DISABLE KEYS */;
INSERT INTO `card_account` VALUES (1,'FI2110000011111111','0B00320D2B'),(2,'FI2130000033333333','0600062E1F'),(3,'FI2150000055555555','06000D5C69'),(4,'FI2170000077777777','06000D5C69');
/*!40000 ALTER TABLE `card_account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transaction_log`
--

DROP TABLE IF EXISTS `transaction_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transaction_log` (
  `id_transaction` int NOT NULL AUTO_INCREMENT,
  `id_account` varchar(20) NOT NULL,
  `transaction_type` varchar(20) NOT NULL,
  `transaction_amount` decimal(10,2) NOT NULL,
  `transaction_time` datetime NOT NULL,
  PRIMARY KEY (`id_transaction`),
  UNIQUE KEY `id_transaction_UNIQUE` (`id_transaction`),
  KEY `id_account_idx` (`id_account`),
  CONSTRAINT `id_account` FOREIGN KEY (`id_account`) REFERENCES `bank_account` (`id_account`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=85 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transaction_log`
--

LOCK TABLES `transaction_log` WRITE;
/*!40000 ALTER TABLE `transaction_log` DISABLE KEYS */;
INSERT INTO `transaction_log` VALUES (1,'FI2110000011111111','deposit',100.00,'2024-04-02 06:53:53'),(2,'FI2110000011111111','withdrawal',200.00,'2024-04-04 17:15:21'),(3,'FI2130000033333333','withdrawal',200.00,'2024-04-04 17:15:34'),(4,'FI2150000055555555','withdrawal',200.00,'2024-04-04 17:15:53'),(5,'FI2170000077777777','withdrawal',200.00,'2024-04-04 17:16:20'),(6,'FI2190000099999999','withdrawal',200.00,'2024-04-04 17:16:36'),(7,'FI2190000099999999','withdrawal',50.00,'2024-04-05 07:56:25'),(8,'FI2110000011111111','withdrawal',100.00,'2024-04-05 08:59:13'),(9,'FI2110000011111111','withdrawal',6.00,'2024-04-05 09:00:27'),(10,'FI2110000011111111','withdrawal',6.00,'2024-04-05 09:00:39'),(11,'FI2110000011111111','deposit',500.00,'2024-04-08 10:44:02'),(12,'FI2110000011111111','withdrawal',20.00,'2024-04-09 05:48:02'),(13,'FI2110000011111111','withdrawal',50.00,'2024-04-09 05:48:24'),(14,'FI2110000011111111','withdrawal',20.00,'2024-04-10 07:46:00'),(15,'FI2130000033333333','withdrawal',50.00,'2024-04-10 07:47:17'),(16,'FI2130000033333333','withdrawal',20.00,'2024-04-10 07:47:31'),(17,'FI2130000033333333','withdrawal',20.00,'2024-04-10 07:48:09'),(18,'FI2130000033333333','withdrawal',40.00,'2024-04-10 07:48:14'),(19,'FI2130000033333333','withdrawal',80.00,'2024-04-10 07:48:18'),(20,'FI2130000033333333','withdrawal',20.00,'2024-04-10 07:48:24'),(21,'FI2130000033333333','withdrawal',20.00,'2024-04-10 07:48:27'),(22,'FI2130000033333333','deposit',100.00,'2024-04-10 07:48:37'),(23,'FI2150000055555555','withdrawal',100.00,'2024-04-10 07:49:08'),(24,'FI2150000055555555','withdrawal',20.00,'2024-04-10 07:49:13'),(25,'FI2150000055555555','withdrawal',50.00,'2024-04-10 07:49:17'),(26,'FI2150000055555555','withdrawal',100.00,'2024-04-10 07:49:20'),(27,'FI2150000055555555','withdrawal',20.00,'2024-04-10 07:49:23'),(28,'FI2170000077777777','withdrawal',20.00,'2024-04-10 07:49:58'),(29,'FI2170000077777777','withdrawal',40.00,'2024-04-10 07:50:01'),(30,'FI2170000077777777','withdrawal',20.00,'2024-04-10 07:50:03'),(31,'FI2170000077777777','withdrawal',50.00,'2024-04-10 07:50:06'),(32,'FI2170000077777777','withdrawal',100.00,'2024-04-10 07:50:08'),(33,'FI2170000077777777','deposit',500.00,'2024-04-10 07:50:19'),(34,'FI2170000077777777','withdrawal',500.00,'2024-04-10 07:50:23'),(35,'FI2170000077777777','withdrawal',20.00,'2024-04-10 07:50:27'),(36,'FI2190000099999999','withdrawal',20.00,'2024-04-10 07:50:49'),(37,'FI2190000099999999','deposit',200.00,'2024-04-10 07:50:57'),(38,'FI2190000099999999','withdrawal',40.00,'2024-04-10 07:51:03'),(39,'FI2190000099999999','withdrawal',80.00,'2024-04-10 07:51:06'),(40,'FI2190000099999999','withdrawal',20.00,'2024-04-10 07:51:08'),(41,'FI2150000055555555','withdrawal',40.00,'2024-04-15 08:28:31'),(42,'FI2170000077777777','withdrawal',240.00,'2024-04-15 08:35:58'),(43,'FI2170000077777777','withdrawal',80.00,'2024-04-15 08:36:36'),(44,'FI2170000077777777','withdrawal',50.00,'2024-04-15 08:40:28'),(45,'FI2150000055555555','withdrawal',20.00,'2024-04-15 08:46:57'),(46,'FI2150000055555555','withdrawal',80.00,'2024-04-15 08:48:28'),(47,'FI2150000055555555','withdrawal',40.00,'2024-04-15 08:49:52'),(48,'FI2170000077777777','withdrawal',40.00,'2024-04-15 08:53:10'),(49,'FI2170000077777777','withdrawal',40.00,'2024-04-15 08:53:25'),(50,'FI2170000077777777','withdrawal',300.00,'2024-04-16 06:56:00'),(51,'FI2150000055555555','withdrawal',300.00,'2024-04-16 06:59:57'),(52,'FI2170000077777777','withdrawal',100.00,'2024-04-16 07:14:36'),(53,'FI2170000077777777','withdrawal',100.00,'2024-04-16 07:14:40'),(54,'FI2170000077777777','withdrawal',80.00,'2024-04-16 07:29:39'),(55,'FI2170000077777777','withdrawal',20.00,'2024-04-16 07:46:09'),(56,'FI2170000077777777','withdrawal',20.00,'2024-04-16 07:46:55'),(57,'FI2150000055555555','withdrawal',20.00,'2024-04-16 07:48:17'),(58,'FI2150000055555555','withdrawal',20.00,'2024-04-16 07:48:27'),(59,'FI2170000077777777','withdrawal',20.00,'2024-04-16 08:04:12'),(60,'FI2170000077777777','withdrawal',20.00,'2024-04-16 08:04:32'),(61,'FI2170000077777777','withdrawal',70.00,'2024-04-16 08:34:59'),(62,'FI2170000077777777','withdrawal',90.00,'2024-04-16 08:35:05'),(63,'FI2170000077777777','withdrawal',110.00,'2024-04-16 08:35:23'),(64,'FI2170000077777777','withdrawal',130.00,'2024-04-16 08:35:40'),(65,'FI2170000077777777','withdrawal',70.00,'2024-04-16 08:54:14'),(66,'FI2170000077777777','withdrawal',90.00,'2024-04-16 08:54:20'),(67,'FI2170000077777777','withdrawal',110.00,'2024-04-16 08:54:26'),(68,'FI2150000055555555','withdrawal',70.00,'2024-04-16 09:02:33'),(69,'FI2170000077777777','withdrawal',90.00,'2024-04-16 09:06:03'),(70,'FI2110000011111111','withdrawal',20.76,'2024-04-16 09:20:28'),(71,'FI2130000033333333','withdrawal',24.76,'2024-04-16 09:21:39'),(72,'FI2150000055555555','withdrawal',24.76,'2024-04-16 09:21:49'),(73,'FI2170000077777777','withdrawal',24.76,'2024-04-16 09:21:57'),(74,'FI2190000099999999','withdrawal',24.76,'2024-04-16 09:22:05'),(75,'FI2130000033333333','withdrawal',20.00,'2024-04-16 11:16:01'),(76,'FI2110000011111111','withdrawal',20.00,'2024-04-16 12:07:21'),(77,'FI2110000011111111','withdrawal',90.00,'2024-04-16 12:07:47'),(78,'FI2110000011111111','withdrawal',20.00,'2024-04-17 07:49:10'),(79,'FI2130000033333333','withdrawal',20.00,'2024-04-17 07:49:58'),(80,'FI2170000077777777','withdrawal',20.00,'2024-04-17 07:50:37'),(81,'FI2150000055555555','withdrawal',0.00,'2024-04-17 07:51:43'),(82,'FI2150000055555555','withdrawal',20.00,'2024-04-17 08:31:40'),(83,'FI2150000055555555','withdrawal',20.00,'2024-04-17 08:41:26'),(84,'FI2150000055555555','withdrawal',20.00,'2024-04-17 15:35:46');
/*!40000 ALTER TABLE `transaction_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `user` (
  `id_user` int NOT NULL AUTO_INCREMENT,
  `fname` varchar(45) NOT NULL,
  `lname` varchar(45) NOT NULL,
  PRIMARY KEY (`id_user`)
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES (9,'Donald','Davies'),(10,'Mickey','Moses'),(11,'Scrooge','McDavies'),(12,'Daisy','Davies'),(13,'Huey','Davies'),(14,'Erkki','Esimerkki');
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_account`
--

DROP TABLE IF EXISTS `user_account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `user_account` (
  `id_useraccount` int NOT NULL AUTO_INCREMENT,
  `id_user` int NOT NULL,
  `id_account` varchar(20) NOT NULL,
  PRIMARY KEY (`id_useraccount`),
  UNIQUE KEY `id_useraccount_UNIQUE` (`id_useraccount`),
  UNIQUE KEY `id_account_UNIQUE` (`id_account`),
  KEY `id_account_idx` (`id_account`),
  KEY `id_user_idx` (`id_user`),
  CONSTRAINT `fk_2_id_account` FOREIGN KEY (`id_account`) REFERENCES `bank_account` (`id_account`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `fk_id_user` FOREIGN KEY (`id_user`) REFERENCES `user` (`id_user`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_account`
--

LOCK TABLES `user_account` WRITE;
/*!40000 ALTER TABLE `user_account` DISABLE KEYS */;
INSERT INTO `user_account` VALUES (1,9,'FI2110000011111111'),(2,10,'FI2130000033333333'),(3,11,'FI2150000055555555'),(4,11,'FI2170000077777777'),(5,12,'FI2190000099999999');
/*!40000 ALTER TABLE `user_account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'bank_automat'
--
/*!50003 DROP PROCEDURE IF EXISTS `bank_transaction` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'REAL_AS_FLOAT,PIPES_AS_CONCAT,ANSI_QUOTES,IGNORE_SPACE,ONLY_FULL_GROUP_BY,ANSI,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER="avnadmin"@"%" PROCEDURE "bank_transaction"(IN account_id VARCHAR(20), IN transaction_type VARCHAR(10), IN amount DECIMAL(10,2))
BEGIN
  DECLARE rows_affected INT DEFAULT 0;

  START TRANSACTION;
  
  IF transaction_type = 'withdrawal' THEN
    UPDATE bank_account 
    SET balance = balance - amount 
    WHERE id_account = account_id AND balance >= amount;
  ELSEIF transaction_type = 'deposit' THEN
    UPDATE bank_account 
    SET balance = balance + amount 
    WHERE id_account = account_id;
  ELSE
    SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Invalid transaction type';
  END IF;

  SET rows_affected = ROW_COUNT();

  IF rows_affected > 0 THEN
    COMMIT;
    INSERT INTO transaction_log(id_account, transaction_type, transaction_amount, transaction_time) 
    VALUES(account_id, transaction_type, amount, NOW());
  ELSE
    ROLLBACK;
  END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
SET @@SESSION.SQL_LOG_BIN = @MYSQLDUMP_TEMP_LOG_BIN;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-04-18  8:55:33
