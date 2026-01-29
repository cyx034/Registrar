--
-- PostgreSQL database dump
--

-- Dumped from database version 17.5
-- Dumped by pg_dump version 17.5

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET transaction_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: course; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.course (
    cno character varying(20) NOT NULL,
    cname character varying(20),
    ccredit character varying(20),
    cacademy character varying(20),
    tno character varying(20)
);


ALTER TABLE public.course OWNER TO postgres;

--
-- Name: sc; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.sc (
    sno character varying(20) NOT NULL,
    cno character varying(20) NOT NULL,
    grade double precision
);


ALTER TABLE public.sc OWNER TO postgres;

--
-- Name: schedule; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.schedule (
    scheduleid character varying(20) NOT NULL,
    term character varying(20),
    acadamy character varying(20),
    major character varying(20),
    gradelevel character varying(10)
);


ALTER TABLE public.schedule OWNER TO postgres;

--
-- Name: schedule_entry; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.schedule_entry (
    entryid character varying(20) NOT NULL,
    scheduleid character varying(20),
    cno character varying(20),
    tno character varying(20),
    "time" character varying(20),
    classroom character varying(20)
);


ALTER TABLE public.schedule_entry OWNER TO postgres;

--
-- Name: student; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.student (
    sno character varying(20) NOT NULL,
    sname character varying(20),
    sacademy character varying(20),
    smajor character varying(20)
);


ALTER TABLE public.student OWNER TO postgres;

--
-- Name: teacher; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.teacher (
    tno character varying(20) NOT NULL,
    tname character varying(20),
    tacademy character varying(20)
);


ALTER TABLE public.teacher OWNER TO postgres;

--
-- Name: tsecretary; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.tsecretary (
    tsno character varying(20) NOT NULL,
    tsname character varying(20),
    tsacademy character varying(20)
);


ALTER TABLE public.tsecretary OWNER TO postgres;

--
-- Data for Name: course; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.course (cno, cname, ccredit, cacademy, tno) FROM stdin;
81001	程序设计基础与语言	4	计算机与信息科学学院	23000001
81002	数据结构	4	计算机与信息科学学院	23000009
81003	数据库系统概论	4	计算机与信息科学学院	23000012
81004	高等数学	5	数学科学学院	23000010
81005	操作系统	4	计算机与信息科学学院	23000002
81006	Python语言	3	计算机与信息科学学院	23000008
81007	离散数学	4	数学科学学院	23000006
81008	线性代数	4	数学科学学院	23000011
\.


--
-- Data for Name: sc; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.sc (sno, cno, grade) FROM stdin;
20240002	81001	74.80000000000001
20240001	81008	-1
20240002	81006	\N
20240001	81001	85.80000000000001
20240001	81007	-1
20240001	81002	85.8
20240002	81004	83.60000000000001
\.


--
-- Data for Name: schedule; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.schedule (scheduleid, term, acadamy, major, gradelevel) FROM stdin;
10001	2024	计算机与信息科学学院	软件工程	2023
10002	2024	数学科学学院	应用数学	2023
10003	2024	计算机与信息科学学院	电子商务	2023
10004	2024	计算机与信息科学学院	智能科学与技术	2023
\.


--
-- Data for Name: schedule_entry; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.schedule_entry (entryid, scheduleid, cno, tno, "time", classroom) FROM stdin;
2000002	\N	81006	23000008	1-16.3.3-4	T209
2000003	10004	81002	23000009	1-16.3.7-8	T303
\.


--
-- Data for Name: student; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.student (sno, sname, sacademy, smajor) FROM stdin;
20240001	李勇	计算机与信息科学学院	软件工程
20240002	刘晨	数学科学学院	信息与计算科学
20240003	王敏	数学科学学院	数学与应用数学
20240004	张立	计算机与信息科学学院	智能科学与技术
20240005	陈新奇	计算机与信息科学学院	软件工程
20240006	赵明	计算机与信息科学学院	电子商务
20240007	王佳佳	数学科学学院	数学与应用数学
\.


--
-- Data for Name: teacher; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.teacher (tno, tname, tacademy) FROM stdin;
23000001	陈明宇	计算机与信息科学学院
23000002	林晓峰	计算机与信息科学学院
23000003	赵琪	计算机与信息科学学院
23000004	吴俊豪	计算机与信息科学学院
23000005	周彤	数学科学学院
23000006	王梓轩	数学科学学院
23000007	刘雨薇	数学科学学院
23000008	龚伟	计算机与信息科学学院
23000009	杨稳	计算机与信息科学学院
23000010	赵候宇	数学科学学院
23000011	莫长鑫	数学科学学院
23000012	肖旋	计算机与信息科学学院
\.


--
-- Data for Name: tsecretary; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.tsecretary (tsno, tsname, tsacademy) FROM stdin;
000001	刘佳怡	计算机与信息科学学院
000002	张涵	数学科学学院
\.


--
-- Name: course course_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.course
    ADD CONSTRAINT course_pkey PRIMARY KEY (cno);


--
-- Name: sc sc_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.sc
    ADD CONSTRAINT sc_pkey PRIMARY KEY (sno, cno);


--
-- Name: schedule_entry schedule_entry_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.schedule_entry
    ADD CONSTRAINT schedule_entry_pkey PRIMARY KEY (entryid);


--
-- Name: schedule schedule_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.schedule
    ADD CONSTRAINT schedule_pkey PRIMARY KEY (scheduleid);


--
-- Name: student student_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.student
    ADD CONSTRAINT student_pkey PRIMARY KEY (sno);


--
-- Name: teacher teacher_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.teacher
    ADD CONSTRAINT teacher_pkey PRIMARY KEY (tno);


--
-- Name: tsecretary tsecretary_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.tsecretary
    ADD CONSTRAINT tsecretary_pkey PRIMARY KEY (tsno);


--
-- Name: course course_tno_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.course
    ADD CONSTRAINT course_tno_fkey FOREIGN KEY (tno) REFERENCES public.teacher(tno);


--
-- Name: sc sc_cno_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.sc
    ADD CONSTRAINT sc_cno_fkey FOREIGN KEY (cno) REFERENCES public.course(cno);


--
-- Name: sc sc_sno_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.sc
    ADD CONSTRAINT sc_sno_fkey FOREIGN KEY (sno) REFERENCES public.student(sno);


--
-- Name: schedule_entry schedule_entry_cno_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.schedule_entry
    ADD CONSTRAINT schedule_entry_cno_fkey FOREIGN KEY (cno) REFERENCES public.course(cno);


--
-- Name: schedule_entry schedule_entry_scheduleid_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.schedule_entry
    ADD CONSTRAINT schedule_entry_scheduleid_fkey FOREIGN KEY (scheduleid) REFERENCES public.schedule(scheduleid);


--
-- Name: schedule_entry schedule_entry_tno_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.schedule_entry
    ADD CONSTRAINT schedule_entry_tno_fkey FOREIGN KEY (tno) REFERENCES public.teacher(tno);


--
-- PostgreSQL database dump complete
--

