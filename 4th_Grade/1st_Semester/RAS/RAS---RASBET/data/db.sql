-- MySQL dump 10.13  Distrib 8.0.29, for Linux (x86_64)
--
-- Host: localhost    Database: projeto_ras
-- ------------------------------------------------------
-- Server version	8.0.31-0ubuntu0.22.04.1

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
-- Table structure for table `Boletim`
--

DROP TABLE IF EXISTS `Boletim`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Boletim` (
  `id` varchar(255) NOT NULL,
  `estado` int NOT NULL,
  `idUser` varchar(255) NOT NULL,
  `data` datetime DEFAULT NULL,
  `montante` double NOT NULL,
  `ganho` double DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `FKBoletim142101` (`idUser`),
  CONSTRAINT `FKBoletim142101` FOREIGN KEY (`idUser`) REFERENCES `User` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Boletim`
--

LOCK TABLES `Boletim` WRITE;
/*!40000 ALTER TABLE `Boletim` DISABLE KEYS */;
INSERT INTO `Boletim` VALUES ('068e5ac2-4bfa-4c6a-9d80-2d7acdd30e39',0,'cento9enta','2022-12-03 12:26:52',122,0),('e79e04a5-437c-42e1-907e-b778ae3e4489',0,'cento9enta','2022-12-03 12:21:25',10,0);
/*!40000 ALTER TABLE `Boletim` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Desporto`
--

DROP TABLE IF EXISTS `Desporto`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Desporto` (
  `desporto` varchar(255) NOT NULL,
  PRIMARY KEY (`desporto`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Desporto`
--

LOCK TABLES `Desporto` WRITE;
/*!40000 ALTER TABLE `Desporto` DISABLE KEYS */;
INSERT INTO `Desporto` VALUES ('Futebol');
/*!40000 ALTER TABLE `Desporto` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Jogo`
--

DROP TABLE IF EXISTS `Jogo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Jogo` (
  `id` varchar(255) NOT NULL,
  `desporto` varchar(255) NOT NULL,
  `data` datetime DEFAULT NULL,
  `estado` int NOT NULL,
  `resultado` varchar(255) DEFAULT NULL,
  `progCorreto` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FKJogo590672` (`desporto`),
  CONSTRAINT `FKJogo590672` FOREIGN KEY (`desporto`) REFERENCES `Desporto` (`desporto`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Jogo`
--

LOCK TABLES `Jogo` WRITE;
/*!40000 ALTER TABLE `Jogo` DISABLE KEYS */;
INSERT INTO `Jogo` VALUES ('01f7c8123fe4ab268ddf4d90bf22bcae','Futebol','2023-01-21 17:00:00',0,NULL,NULL),('0c33b89a2f86957ebbe2584ff87754b2','Futebol','2022-12-28 15:30:00',2,NULL,NULL),('0d660333cea680040744c67e9cd77534','Futebol','2023-01-16 19:01:12',1,'2x0','Estoril'),('282fed58a147325e5b0afffcaa1a0e87','Futebol','2022-12-28 15:30:00',3,NULL,NULL),('3374a5219c3d6f050bd3109903b679c4','Futebol','2022-12-28 15:30:00',0,NULL,NULL),('44ef1caee7739164c7e52a771a658b4c','Futebol','2023-01-21 20:30:00',0,NULL,NULL),('522b83747b682421bde9063e6d923cc9','Futebol','2023-01-22 20:30:00',0,NULL,NULL),('52937650c1f4edbce02009268a033498','Futebol','2023-01-20 21:15:00',0,NULL,NULL),('59d90eb97cea82f8adb63799b09a6e07','Futebol','2023-01-23 20:15:00',0,NULL,NULL),('7fc7f4e73a187a777be3954f758e9577','Futebol','2023-01-16 21:15:06',1,'2x1','Gil Vicente'),('873b384613f3e472f7f6078760d66f5c','Futebol','2022-12-28 15:30:00',0,NULL,NULL),('8b300830a0ebd20cee78596230305039','Futebol','2023-01-22 15:30:00',0,NULL,NULL),('8f1568cea6b0d4db20ef3bb0aaa54f61','Futebol','2023-01-21 15:30:00',0,NULL,NULL),('923f451c2663e29d50cdb0027ab20ea7','Futebol','2022-12-28 15:30:00',0,NULL,NULL),('93e4f30c5f066fd35e1fbce9fac715c1','Futebol','2023-01-22 18:00:00',0,NULL,NULL),('94f9a296ef2f0a2f72553baf8b79741b','Futebol','2022-12-28 15:30:00',0,NULL,NULL),('94f9f4d2245188d30d7429ddad9178b1','Futebol','2023-01-15 15:33:01',1,'1x1','Arouca'),('ad72eab7e549220ad0907a783a3c6b77','Futebol','2023-01-15 18:02:34',1,'2x2','Sporting Lisbon'),('bce78d6897dc1da6e3bbda794b0751ca','Futebol','2023-01-20 19:00:00',0,NULL,NULL),('be6439e02cf1993457751f2e4e6c1d74','Futebol','2023-01-15 20:31:28',1,'4x1','FC Porto'),('e913fe08c63882e6675a3137d2aa2260','Futebol','2022-12-28 15:30:00',0,NULL,NULL),('ec2f72299349bba6d9e7e979d0e7d6d8','Futebol','2022-12-28 15:30:00',0,NULL,NULL),('f03db53acb1492a8930663127323502e','Futebol','2022-12-28 15:30:00',0,NULL,NULL);
/*!40000 ALTER TABLE `Jogo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Notificacao`
--

DROP TABLE IF EXISTS `Notificacao`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Notificacao` (
  `id` varchar(255) NOT NULL,
  `enviarTodos` binary(1) NOT NULL,
  `idUser` varchar(255) DEFAULT NULL,
  `text` varchar(255) NOT NULL,
  `idTrabalhador` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FKNotificaca964914` (`idUser`),
  CONSTRAINT `FKNotificaca964914` FOREIGN KEY (`idUser`) REFERENCES `User` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Notificacao`
--

LOCK TABLES `Notificacao` WRITE;
/*!40000 ALTER TABLE `Notificacao` DISABLE KEYS */;
INSERT INTO `Notificacao` VALUES ('0c662f44-956a-4181-8227-76705c0b956b',_binary '0','cento9enta','As odds do jogo Benfica vs Sporting Lisbonforam alteradas!','ad72eab7e549220ad0907a783a3c6b77'),('22a830fb-504e-4ea4-a929-76a0b60724e3',_binary '1',NULL,'   ','danibala23'),('3db32bd4-c468-4ac2-94c0-c6921d7b06dd',_binary '0','cento9enta','O seu pedido de ajuda foi respondido com sucesso, aceda ao mesmo através da sua area de notificações','grodd'),('41978b25-2bd3-4ee2-9df0-d645a17ee0ec',_binary '0','cento9enta','Olá','danibala23'),('495bae05-b150-4511-85e8-fac6f7514004',_binary '1',NULL,'promoção no boavista porto','danibala23'),('654e4fd1-f6b3-4d8d-bd73-b392eeb03fe9',_binary '1',NULL,'aproveita','danibala23'),('844ba359-1cbf-4fcd-a58d-c71ad3be6ca0',_binary '1',NULL,'sss','danibala23'),('efd08369-9390-4544-9c44-6f5901b3ca13',_binary '0','cento9enta','O seu pedido de ajuda foi respondido com sucesso, aceda ao mesmo através da sua area de notificações','grodd');
/*!40000 ALTER TABLE `Notificacao` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `NotificacaoLida`
--

DROP TABLE IF EXISTS `NotificacaoLida`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `NotificacaoLida` (
  `id` varchar(255) NOT NULL,
  `idUser` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `FKNotificaca486491` (`idUser`),
  CONSTRAINT `FKNotificaca486491` FOREIGN KEY (`idUser`) REFERENCES `User` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FKNotificaca924321` FOREIGN KEY (`id`) REFERENCES `Notificacao` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `NotificacaoLida`
--

LOCK TABLES `NotificacaoLida` WRITE;
/*!40000 ALTER TABLE `NotificacaoLida` DISABLE KEYS */;
/*!40000 ALTER TABLE `NotificacaoLida` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Observar`
--

DROP TABLE IF EXISTS `Observar`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Observar` (
  `idUser` varchar(255) NOT NULL,
  `idJogo` varchar(255) NOT NULL,
  PRIMARY KEY (`idUser`,`idJogo`),
  KEY `idJogo` (`idJogo`),
  CONSTRAINT `Observar_ibfk_1` FOREIGN KEY (`idUser`) REFERENCES `User` (`id`),
  CONSTRAINT `Observar_ibfk_2` FOREIGN KEY (`idJogo`) REFERENCES `Jogo` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Observar`
--

LOCK TABLES `Observar` WRITE;
/*!40000 ALTER TABLE `Observar` DISABLE KEYS */;
INSERT INTO `Observar` VALUES ('cento9enta','f03db53acb1492a8930663127323502e');
/*!40000 ALTER TABLE `Observar` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Odds`
--

DROP TABLE IF EXISTS `Odds`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Odds` (
  `idJogo` varchar(255) NOT NULL,
  `prognostico` varchar(255) NOT NULL,
  `valor` double DEFAULT NULL,
  PRIMARY KEY (`idJogo`,`prognostico`),
  CONSTRAINT `odds_ibfk_1` FOREIGN KEY (`idJogo`) REFERENCES `Jogo` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Odds`
--

LOCK TABLES `Odds` WRITE;
/*!40000 ALTER TABLE `Odds` DISABLE KEYS */;
INSERT INTO `Odds` VALUES ('01f7c8123fe4ab268ddf4d90bf22bcae','Benfica',1),('01f7c8123fe4ab268ddf4d90bf22bcae','Draw',4),('01f7c8123fe4ab268ddf4d90bf22bcae','Santa Clara',8),('0c33b89a2f86957ebbe2584ff87754b2','Boavista Porto',3),('0c33b89a2f86957ebbe2584ff87754b2','Draw',NULL),('0c33b89a2f86957ebbe2584ff87754b2','Estoril',2),('0d660333cea680040744c67e9cd77534','Casa Pia',34),('0d660333cea680040744c67e9cd77534','Draw',29),('0d660333cea680040744c67e9cd77534','Estoril',1),('282fed58a147325e5b0afffcaa1a0e87','Arouca',17),('282fed58a147325e5b0afffcaa1a0e87','Draw',10),('282fed58a147325e5b0afffcaa1a0e87','FC Porto',1),('3374a5219c3d6f050bd3109903b679c4','Chaves',2),('3374a5219c3d6f050bd3109903b679c4','Draw',3),('3374a5219c3d6f050bd3109903b679c4','Famalicão',3),('44ef1caee7739164c7e52a771a658b4c','Draw',4),('44ef1caee7739164c7e52a771a658b4c','FC Porto',1),('44ef1caee7739164c7e52a771a658b4c','Vitória SC',7),('522b83747b682421bde9063e6d923cc9','Draw',3),('522b83747b682421bde9063e6d923cc9','Famalicão',2),('522b83747b682421bde9063e6d923cc9','Rio Ave FC',3),('52937650c1f4edbce02009268a033498','Draw',5),('52937650c1f4edbce02009268a033498','Sporting Lisbon',1),('52937650c1f4edbce02009268a033498','Vizela',10),('59d90eb97cea82f8adb63799b09a6e07','Boavista Porto',2),('59d90eb97cea82f8adb63799b09a6e07','Chaves',3),('59d90eb97cea82f8adb63799b09a6e07','Draw',3),('7fc7f4e73a187a777be3954f758e9577','Draw',3),('7fc7f4e73a187a777be3954f758e9577','Gil Vicente',5),('7fc7f4e73a187a777be3954f758e9577','Vitória SC',1),('873b384613f3e472f7f6078760d66f5c','Casa Pia',3),('873b384613f3e472f7f6078760d66f5c','Draw',3),('873b384613f3e472f7f6078760d66f5c','Portimonense',2),('8b300830a0ebd20cee78596230305039','CS Maritimo',2),('8b300830a0ebd20cee78596230305039','Draw',3),('8b300830a0ebd20cee78596230305039','Estoril',2),('8f1568cea6b0d4db20ef3bb0aaa54f61','Braga',1),('8f1568cea6b0d4db20ef3bb0aaa54f61','Draw',4),('8f1568cea6b0d4db20ef3bb0aaa54f61','Pacos de Ferreira',6),('923f451c2663e29d50cdb0027ab20ea7','Benfica',1),('923f451c2663e29d50cdb0027ab20ea7','Braga',3),('923f451c2663e29d50cdb0027ab20ea7','Draw',3),('93e4f30c5f066fd35e1fbce9fac715c1','Casa Pia',2),('93e4f30c5f066fd35e1fbce9fac715c1','Draw',3),('93e4f30c5f066fd35e1fbce9fac715c1','Gil Vicente',3),('94f9a296ef2f0a2f72553baf8b79741b','Draw',3),('94f9a296ef2f0a2f72553baf8b79741b','Gil Vicente',2),('94f9a296ef2f0a2f72553baf8b79741b','Santa Clara',3),('94f9f4d2245188d30d7429ddad9178b1','Arouca',27),('94f9f4d2245188d30d7429ddad9178b1','Chaves',17),('94f9f4d2245188d30d7429ddad9178b1','Draw',1),('ad72eab7e549220ad0907a783a3c6b77','Benfica',12),('ad72eab7e549220ad0907a783a3c6b77','Draw',8),('ad72eab7e549220ad0907a783a3c6b77','Sporting Lisbon',28),('bce78d6897dc1da6e3bbda794b0751ca','Arouca',2),('bce78d6897dc1da6e3bbda794b0751ca','Draw',3),('bce78d6897dc1da6e3bbda794b0751ca','Portimonense',3),('be6439e02cf1993457751f2e4e6c1d74','Draw',29),('be6439e02cf1993457751f2e4e6c1d74','Famalicão',34),('be6439e02cf1993457751f2e4e6c1d74','FC Porto',1),('e913fe08c63882e6675a3137d2aa2260','Draw',3),('e913fe08c63882e6675a3137d2aa2260','Vitória SC',3),('e913fe08c63882e6675a3137d2aa2260','Vizela',2),('ec2f72299349bba6d9e7e979d0e7d6d8','CS Maritimo',3),('ec2f72299349bba6d9e7e979d0e7d6d8','Draw',3),('ec2f72299349bba6d9e7e979d0e7d6d8','Rio Ave FC',2),('f03db53acb1492a8930663127323502e','Draw',8),('f03db53acb1492a8930663127323502e','Pacos de Ferreira',17),('f03db53acb1492a8930663127323502e','Sporting Lisbon',1);
/*!40000 ALTER TABLE `Odds` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `PedidoAjuda`
--

DROP TABLE IF EXISTS `PedidoAjuda`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `PedidoAjuda` (
  `userApostador` varchar(255) NOT NULL,
  `userTecnico` varchar(255) DEFAULT NULL,
  `data` datetime DEFAULT NULL,
  `texto` varchar(255) NOT NULL,
  `resposta` varchar(255) DEFAULT NULL,
  KEY `FKPedidoAjud699805` (`userApostador`),
  KEY `FKPedidoAjud999602` (`userTecnico`),
  CONSTRAINT `FKPedidoAjud699805` FOREIGN KEY (`userApostador`) REFERENCES `User` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FKPedidoAjud999602` FOREIGN KEY (`userTecnico`) REFERENCES `User` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `PedidoAjuda`
--

LOCK TABLES `PedidoAjuda` WRITE;
/*!40000 ALTER TABLE `PedidoAjuda` DISABLE KEYS */;
INSERT INTO `PedidoAjuda` VALUES ('cento9enta',NULL,'2022-12-02 23:43:52','eRRO AO ACEDER AS APOSTAS',NULL);
/*!40000 ALTER TABLE `PedidoAjuda` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Prognostico`
--

DROP TABLE IF EXISTS `Prognostico`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Prognostico` (
  `idBoletim` varchar(255) NOT NULL,
  `idJogo` varchar(255) NOT NULL,
  `prognostico` varchar(255) NOT NULL,
  `valor` double NOT NULL,
  PRIMARY KEY (`idBoletim`,`idJogo`),
  KEY `FKAposta197359` (`idBoletim`),
  KEY `idJogo` (`idJogo`,`prognostico`),
  CONSTRAINT `Aposta_ibfk_1` FOREIGN KEY (`idJogo`, `prognostico`) REFERENCES `Odds` (`idJogo`, `prognostico`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FKAposta197359` FOREIGN KEY (`idBoletim`) REFERENCES `Boletim` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Prognostico`
--

LOCK TABLES `Prognostico` WRITE;
/*!40000 ALTER TABLE `Prognostico` DISABLE KEYS */;
INSERT INTO `Prognostico` VALUES ('068e5ac2-4bfa-4c6a-9d80-2d7acdd30e39','0c33b89a2f86957ebbe2584ff87754b2','Draw',20),('e79e04a5-437c-42e1-907e-b778ae3e4489','0c33b89a2f86957ebbe2584ff87754b2','Draw',3),('e79e04a5-437c-42e1-907e-b778ae3e4489','282fed58a147325e5b0afffcaa1a0e87','Draw',7);
/*!40000 ALTER TABLE `Prognostico` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Promocao`
--

DROP TABLE IF EXISTS `Promocao`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Promocao` (
  `id` varchar(255) NOT NULL,
  `idJogo` varchar(255) NOT NULL,
  `prognostico` varchar(255) NOT NULL,
  `oddMelhorada` double DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `prognosticoUnico` (`idJogo`,`prognostico`),
  KEY `FKPromocao908920` (`idJogo`),
  CONSTRAINT `FKPromocao908920` FOREIGN KEY (`idJogo`) REFERENCES `Jogo` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Promocao`
--

LOCK TABLES `Promocao` WRITE;
/*!40000 ALTER TABLE `Promocao` DISABLE KEYS */;
INSERT INTO `Promocao` VALUES ('222','0c33b89a2f86957ebbe2584ff87754b2','Draw',20),('deca64cc-ca2c-45a0-bc4c-d3f6e9cf7071','0c33b89a2f86957ebbe2584ff87754b2','Boavista Porto',24),('df3a03b8-0ac0-48d2-a73b-87ca8c08fa66','873b384613f3e472f7f6078760d66f5c','Draw',5);
/*!40000 ALTER TABLE `Promocao` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `PromocaoUsada`
--

DROP TABLE IF EXISTS `PromocaoUsada`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `PromocaoUsada` (
  `idPromo` varchar(255) NOT NULL,
  `idUser` varchar(255) NOT NULL,
  `idJogo` varchar(255) NOT NULL,
  PRIMARY KEY (`idPromo`,`idUser`),
  KEY `FKPromocaoUs427753` (`idUser`),
  KEY `FKPromocaoUs90726` (`idJogo`),
  KEY `FKPromocaoUs239225` (`idPromo`),
  CONSTRAINT `FKPromocaoUs239225` FOREIGN KEY (`idPromo`) REFERENCES `Promocao` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FKPromocaoUs427753` FOREIGN KEY (`idUser`) REFERENCES `User` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FKPromocaoUs90726` FOREIGN KEY (`idJogo`) REFERENCES `Jogo` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `PromocaoUsada`
--

LOCK TABLES `PromocaoUsada` WRITE;
/*!40000 ALTER TABLE `PromocaoUsada` DISABLE KEYS */;
/*!40000 ALTER TABLE `PromocaoUsada` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Transacao`
--

DROP TABLE IF EXISTS `Transacao`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Transacao` (
  `id` varchar(255) NOT NULL,
  `date` datetime NOT NULL,
  `idUser` varchar(255) NOT NULL,
  `tipo` binary(1) NOT NULL,
  `valor` double DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `FKTransacao216557` (`idUser`),
  CONSTRAINT `FKTransacao216557` FOREIGN KEY (`idUser`) REFERENCES `User` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Transacao`
--

LOCK TABLES `Transacao` WRITE;
/*!40000 ALTER TABLE `Transacao` DISABLE KEYS */;
INSERT INTO `Transacao` VALUES ('33ba41f9-3f68-4546-830b-ad0b10fc14ff','2022-12-03 10:18:17','cento9enta',_binary '0',13),('464d3336-857c-450f-a4d8-4e422b1c05cf','2022-12-03 11:57:52','cento9enta',_binary '0',400),('a4502073-429f-451b-a430-ac31875e8b21','2022-12-02 23:11:02','cento9enta',_binary '1',10),('a947633a-2aba-4089-a481-32bde8d348ea','2022-12-02 23:10:44','cento9enta',_binary '0',100);
/*!40000 ALTER TABLE `Transacao` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `User`
--

DROP TABLE IF EXISTS `User`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `User` (
  `id` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `email` varchar(255) NOT NULL,
  `nome` varchar(255) NOT NULL,
  `dataNascimento` datetime NOT NULL,
  `logado` binary(1) NOT NULL,
  `idFiscal` varchar(255) NOT NULL,
  `idCivil` varchar(255) NOT NULL,
  `tipo` int NOT NULL,
  `saldo` double DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `email` (`email`),
  UNIQUE KEY `idFiscal` (`idFiscal`),
  UNIQUE KEY `idCivil` (`idCivil`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `User`
--

LOCK TABLES `User` WRITE;
/*!40000 ALTER TABLE `User` DISABLE KEYS */;
INSERT INTO `User` VALUES ('cento9enta','Henrique07','henriquealvelos@gmail.com','Henrique Alvelos','2001-12-05 00:00:00',_binary '1','123456789','123456789',0,156),('danibala23','dani','danielxavier@gmail.com','Daniel Xavier','2001-01-01 00:00:00',_binary '0','123321','123321',3,0),('grodd','gro','duartecerquido@gmail.com','Duarte Cerquido','2001-01-01 00:00:00',_binary '0','12332145','12332145',1,0),('purp','senhas','diogorebelo@gmail.com','Diogo Rebelo','2001-01-01 00:00:00',_binary '0','123321456','123321456',0,0),('tuberacher','tube','juliogoncalves@gmail.com','Júlio Gonçalves','2001-01-01 00:00:00',_binary '1','1233214','1233214',2,0);
/*!40000 ALTER TABLE `User` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-01-18 10:56:48
