-- MySQL dump 10.13  Distrib 8.0.27, for Win64 (x86_64)
--
-- Host: localhost    Database: uczelnia
-- ------------------------------------------------------
-- Server version	8.0.27

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

--
-- Table structure for table `kierunek_wydzial`
--

DROP TABLE IF EXISTS `kierunek_wydzial`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `kierunek_wydzial` (
  `id` int NOT NULL AUTO_INCREMENT,
  `kierunek` varchar(50) NOT NULL,
  `kod_wydzialu` varchar(50) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `rel5` (`kod_wydzialu`),
  KEY `kierunek` (`kierunek`),
  CONSTRAINT `kierunek_wydzial_ibfk_1` FOREIGN KEY (`kierunek`) REFERENCES `wydzialy` (`kod_wydz`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `kierunek_wydzial`
--

LOCK TABLES `kierunek_wydzial` WRITE;
/*!40000 ALTER TABLE `kierunek_wydzial` DISABLE KEYS */;
/*!40000 ALTER TABLE `kierunek_wydzial` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `oceny`
--

DROP TABLE IF EXISTS `oceny`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `oceny` (
  `nazwa_przedmiotu` varchar(20) NOT NULL,
  `ocena` enum('2.0','3.0','3.5','4.0','4.5','5.0') DEFAULT NULL,
  `nr_indeksu_tabela` int NOT NULL,
  `id` int NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`),
  KEY `rel2` (`nr_indeksu_tabela`),
  CONSTRAINT `rel2` FOREIGN KEY (`nr_indeksu_tabela`) REFERENCES `tabela` (`nr_indeksu`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `oceny`
--

LOCK TABLES `oceny` WRITE;
/*!40000 ALTER TABLE `oceny` DISABLE KEYS */;
INSERT INTO `oceny` VALUES ('Analiza','4.0',116582,1),('Algebra','3.5',116581,2);
/*!40000 ALTER TABLE `oceny` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `osoby`
--

DROP TABLE IF EXISTS `osoby`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `osoby` (
  `id` int NOT NULL AUTO_INCREMENT,
  `imie` varchar(20) NOT NULL,
  `nazwisko` varchar(20) NOT NULL,
  `plec` varchar(1) NOT NULL,
  `data_ur` date NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `osoby`
--

LOCK TABLES `osoby` WRITE;
/*!40000 ALTER TABLE `osoby` DISABLE KEYS */;
INSERT INTO `osoby` VALUES (1,'Kamil','Gancarczyk','M','2010-11-13'),(3,'Daniel','Jaki','M','1994-10-29'),(4,'Jacek','Kowal','M','1994-10-02'),(5,'Gosia','Zajac','K','1994-01-12'),(6,'Kamila','Wegrzyn','K','1994-10-18'),(7,'Kasia','Jankowska','K','1994-10-29'),(9,'Dawid','Parzyk','M','2000-11-13'),(10,'John','John','K','2001-01-01'),(11,'John','John','M','2001-01-01');
/*!40000 ALTER TABLE `osoby` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pracownik`
--

DROP TABLE IF EXISTS `pracownik`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `pracownik` (
  `id` int NOT NULL AUTO_INCREMENT,
  `imie` varchar(45) NOT NULL,
  `nazwisko` varchar(45) NOT NULL,
  `data_ur` date NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pracownik`
--

LOCK TABLES `pracownik` WRITE;
/*!40000 ALTER TABLE `pracownik` DISABLE KEYS */;
/*!40000 ALTER TABLE `pracownik` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `studia`
--

DROP TABLE IF EXISTS `studia`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `studia` (
  `nr_indeksu_tabela` int NOT NULL,
  `kierunek` varchar(20) DEFAULT NULL,
  `id` int NOT NULL,
  PRIMARY KEY (`id`),
  KEY `rel3` (`nr_indeksu_tabela`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `studia`
--

LOCK TABLES `studia` WRITE;
/*!40000 ALTER TABLE `studia` DISABLE KEYS */;
INSERT INTO `studia` VALUES (116581,'prawo',1),(116582,'informatyka',2),(116583,'informatyka',3),(116584,'medycyna',4),(116585,'informatyka',5),(116586,'socjologia',6),(116587,'informatyka',7);
/*!40000 ALTER TABLE `studia` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tabela`
--

DROP TABLE IF EXISTS `tabela`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tabela` (
  `id_osoby` int NOT NULL,
  `nr_indeksu` int NOT NULL,
  `id` int NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`),
  UNIQUE KEY `moj_index` (`nr_indeksu`),
  KEY `tabela_ibfk_1` (`id_osoby`),
  CONSTRAINT `tabela_ibfk_1` FOREIGN KEY (`id_osoby`) REFERENCES `osoby` (`id`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tabela`
--

LOCK TABLES `tabela` WRITE;
/*!40000 ALTER TABLE `tabela` DISABLE KEYS */;
INSERT INTO `tabela` VALUES (1,116587,1),(3,116582,3),(4,116583,4),(5,116584,5),(6,116585,6),(7,116586,7),(9,116581,11);
/*!40000 ALTER TABLE `tabela` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `wydzialy`
--

DROP TABLE IF EXISTS `wydzialy`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `wydzialy` (
  `kod_wydz` varchar(50) NOT NULL,
  `nazwa_wydz` varchar(50) NOT NULL,
  PRIMARY KEY (`kod_wydz`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `wydzialy`
--

LOCK TABLES `wydzialy` WRITE;
/*!40000 ALTER TABLE `wydzialy` DISABLE KEYS */;
/*!40000 ALTER TABLE `wydzialy` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-02-01  0:38:46
